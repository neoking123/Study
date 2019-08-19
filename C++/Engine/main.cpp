#include "Game2D.h"
#include "RandomNumberGenerator.h"

namespace neoking
{
	class Example : public Game2D
	{
	public:
		void update() override
		{
			// draw a house
			beginTransformation();
			{
				// wall
				//drawFilledBox(Colors::yellow, 0.2f, 0.2f);

				// roof
				drawWiredTriangle(Colors::red, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });
				drawFilledTriangle(Colors::red, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });
				

				// window
				//drawFilledBox(Colors::skyblue, 0.1f, 0.1f);
				//drawWiredBox(Colors::gray, 0.1f, 0.1f);
				//drawLine(Colors::gray, { 0.0f, -0.05f }, Colors::gray, { 0.0f, 0.05f });
				//drawLine(Colors::gray, { -0.05f, 0.0f }, Colors::gray, { 0.05f, 0.0f });

			}
			endTransformation();
		}
	};

	class TransformExample : public Game2D
	{
	public:
		float time;

		void update() override
		{
			/*rotate(time * -90.0f);
			drawFilledStar(Colors::gold, 0.4f, 0.25f);

			time += getTimeStep();*/
			
		}
	};
}

int main(void)
{
	//neoking::Example().run();
	neoking::TransformExample().run();
	//neoking::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//neoking::PrimitivesGallery().run();

	return 0;
}
