#pragma once
#include "App.h"
#include "Renderer.h"
#include "Audio.h"

App::App()
{
	
}

App::~App() {
   
}

void App::MainLoop()
{	
		Renderer renderer;
		Audio audio;

		audio.OpenFile("audio.mp3");


		while (!renderer.WindowShouldClose) {
			
			audio.UseFFT(renderer.UseFFT);
			audio.UseSmooth(renderer.UseSmooth);
			audio.SmoothStep(renderer.smoothStep);
			audio.SegmentLenght(renderer.segmentLenght);

			if(renderer.play)
				audio.Step();

			renderer.Draw(audio.Out);


		}
		audio.CloseFile();

}

