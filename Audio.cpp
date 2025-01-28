

#pragma once
#include "Audio.h"
#include <algorithm>


Audio::Audio()
{
}

Audio::~Audio()
{
}

int Audio::OpenFile(const char* path)
{
    if (File_opened) {
        std::cout << "File is alredy opened:" << sf_strerror(infile) << std::endl;
        return -1;
    }


    infile = sf_open(path, SFM_READ, &sfInfo);
    if (!infile) {
        std::cout << "Error of opening file: " << sf_strerror(infile) << std::endl;
        return -1;
    }
    

    File_opened = true;
    return 0;
}

int Audio::CloseFile()
{
    if (File_opened and sf_close(infile)) {
        std::cout << "Error close of file: " << sf_strerror(infile) << std::endl;
        return -1;
    }
    File_opened = false;




    return 0;
}

void Audio::UseFFT(bool useFFT)
{
    this->useFFT = useFFT;
}

void Audio::UseSmooth(bool useSmooth)
{
    this->useSmooth = useSmooth;
}

void Audio::SmoothStep(int smoothStep)
{
    this->smoothStep = smoothStep;
}

void Audio::SegmentLenght(int segmentLength)
{
    this->segmentLength = segmentLength;
}

void Audio::Step()
{   
  
    this->ReadData();
    this->AnalyzeFFT();
    this->SmoothFFT();

    //this->Normalize();

    this->AudioData.shrink_to_fit();
    this->FFTData.shrink_to_fit();
    this->FFTData_temp.shrink_to_fit();

}



void Audio::ReadData()
{
    startSample += sfInfo.samplerate / 60;
    // Проверяем, что сегмент не выходит за пределы файла
    
    if ((startSample + segmentLength) > sfInfo.frames) {
        
        if (File_opened) {
            std::cout << "End of file" << std::endl;
            sf_close(infile);
            File_opened = false;
        }
    }
    else {
        // Читаем только нужный сегмент из файла
        AudioData.clear();
        AudioData.resize(segmentLength * sfInfo.channels, 0);
        sf_seek(infile, startSample, SEEK_SET); // Перемещаем указатель на нужную позицию
        sf_readf_double(infile, AudioData.data(), segmentLength); // Читаем сегмент
    }

    if (!useFFT) {
        
        Out.clear();
        Out.reserve(AudioData.size());
        for (size_t i = 0; i < AudioData.size();i++) {
            Out.push_back(AudioData[i]*40);
        }

    }
}

void Audio::AnalyzeFFT(){

        FFTData.clear();
        

        // Подготовка для FFT
        std::size_t N = static_cast<std::size_t>(segmentLength); // Количество отсчетов в сегменте
        double fs = sfInfo.samplerate; // Частота дискретизации
        std::vector<std::complex<double>> out(N);

        /* for (size_t i = 0; i < segmentLength * sfInfo.channels;i++)
                FFTData.push_back(buffer[i]*100);*/


                // Создаем план FFTW
        fftw_plan plan = fftw_plan_dft_r2c_1d(N, AudioData.data(), reinterpret_cast<fftw_complex*>(out.data()), FFTW_ESTIMATE);

        // Выполнение FFT
        fftw_execute(plan);
        std::vector<double> amplitudes;

        for (const auto& x : out) {
            amplitudes.push_back(sqrt(x.real() * x.real())); // std::abs вычисляет модуль комплексного числа
        }
        //amplitudes[0] = 0.;
        /*double max_amplitude = *std::max_element(amplitudes.begin(), amplitudes.end());
        if (max_amplitude == 0.0) {
            max_amplitude = 1;
        }*/
        //double max_amplitude = 1;


        //for (std::size_t k = 0; k < N / 2 + 1; ++k) { // Для действительных частот
        //     double frequency = static_cast<double>(k) * fs / N; // Расчет частоты
        //     //if ((amplitudes[k] / max_amplitude) < 0.8) { continue; }
        //     std::cout << std::fixed << "frequency: " << frequency << "Hz\t" << "ampl: " << out[k].real() << "\t" << "image: " << out[k].imag() << "\n";
        // }
        //std::cout << startSample << "/" << sfInfo.frames << std::endl;

        // std::cout << std::endl << std::endl << std::endl;


        //double bass = 0;
        //double maxFrequencyOfBass = 0;
        //double medium = 0;
        //double maxFrequencyOfMedium = 0;
        //double high = 0;
        ///*for (size_t i = 0; i < 7; ++i) {
        //    double frequency = static_cast<double>(i) * fs / N;
        //    bass =std::max(bass, (amplitudes[i] / max_amplitude));
        //    maxFrequencyOfBass = frequency;
        //}*/
        //bass = amplitudes[1];
        //medium = amplitudes[100];
        //high = amplitudes[200];

        if (useFFT) {
            Out.clear();
            Out.reserve(N/4+1);
            for (size_t i = 0; i < N / 4 + 1;i++) {
                Out.push_back(amplitudes[i]);
            }
        }
        /*else {
            for (size_t i = 0; i < (segmentLength * sfInfo.channels);i++) {
                FFTData.push_back(AudioData[i] * 100);
            }
        }*/


        // N/2 - 22050
        // N/4 - 11025к
        // N/8 - 5512


        // Освобождение ресурсов
        fftw_destroy_plan(plan);
        //system("pause");
        
}
void Audio::SmoothFFT()
{ 
    if (useSmooth) {
        if (Out.size() != FFTData_temp.size()) {
            FFTData_temp.clear();
            for (auto t : Out) {
                FFTData_temp.push_back(t);
            }
        }

        for (size_t i = 0;i < Out.size();i++) {
            FFTData_temp[i] = FFTData_temp[i] + ((Out[i] - FFTData_temp[i]) / smoothStep);
            Out[i] = FFTData_temp[i];
        }
    }
    else {
        FFTData_temp.clear();
    }
}

void Audio::Normalize()
{
    double max = *std::max_element(Out.begin(), Out.end());
    for (size_t i = 0;i < Out.size();i++) {
        Out[i] /= max;
        Out[i] *= 75;
    }


}
