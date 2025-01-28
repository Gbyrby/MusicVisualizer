#include <sndfile.h>
#include <fftw3.h>
#include <iostream>
#include <vector>
#include <complex>
#include <portaudio.h>

class Audio {
public:
	Audio();
	~Audio();

	int OpenFile(const char* path);
	int CloseFile();

	void UseFFT(bool useFFT);
	void UseSmooth(bool useSmooth);
	void SmoothStep(int smoothStep );
	void SegmentLenght(int segmentLength);
	void Step();


	std::vector<double> FFTData;
	std::vector<double> AudioData;
	std::vector<double> Out;

private:

	void ReadData();
	void AnalyzeFFT();
	void SmoothFFT();
	void Normalize();
	SF_INFO sfInfo;
	SNDFILE* infile;

	int startSample = 0;
	int segmentLength = 2048/2; // Длина сегмента (например, 2048 отсчетов)
	bool File_opened = false;

	bool useFFT = true;
	bool useSmooth = true;
	int smoothStep = 10;
	std::vector<double> FFTData_temp;

};