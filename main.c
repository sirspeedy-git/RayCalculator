#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "tinyexpr.h"


//should take in a string with a mathmatical expsresion and return the correct value "(2+1)+3*5" = 18 
double evaluate(char* expresion);

int main() {
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(325, 450, "Calculator");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	float rotation = 0.0f;
	int spin = 0;
	bool showMessageBox = false;
	Vector2 wabV = { 200, 400 };

	char prevOp[100] = "";
	char currOp[100] = "";

	// game loop
	while (!WindowShouldClose()){		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

		GuiDrawRectangle((Rectangle) { 13, 48, 300, 22 }, 1, BLACK, WHITE);
		DrawText(prevOp, 15, 50, 20, BLACK);
		
		GuiDrawRectangle((Rectangle) { 13, 48+24, 300, 22 }, 1, BLACK, WHITE);
		DrawText(currOp, 15, 50+24, 20, BLACK);

		// 7 8 9 /
		// 4 5 6 *
		// 1 2 3 +
		// 0 < c =

		if (GuiButton((Rectangle) { 5 + 0 * 62, 180 + 3 * 62, 60, 60 }, "0")) {
			strcat(currOp, "0");
		}
		if (GuiButton((Rectangle) { 5 + 0 * 62, 180 + 2 * 62, 60, 60 }, "1")) {
			strcat(currOp, "1");
		}
		if (GuiButton((Rectangle) { 5 + 1 * 62, 180 + 2 * 62, 60, 60 }, "2")) {
			strcat(currOp, "2");
		}
		if (GuiButton((Rectangle) { 5 + 2 * 62, 180 + 2 * 62, 60, 60 }, "3")) {
			strcat(currOp, "3");
		}
		if (GuiButton((Rectangle) { 5 + 0 * 62, 180 + 1 * 62, 60, 60 }, "4")) {
			strcat(currOp, "4");
		}
		if (GuiButton((Rectangle) { 5 + 1 * 62, 180 + 1 * 62, 60, 60 }, "5")) {
			strcat(currOp, "5");
		}
		if (GuiButton((Rectangle) { 5 + 2 * 62, 180 + 1 * 62, 60, 60 }, "6")) {
			strcat(currOp, "6");
		}
		if (GuiButton((Rectangle) { 5 + 0 * 62, 180 + 0 * 62, 60, 60 }, "7")) {
			strcat(currOp, "7");
		}
		if (GuiButton((Rectangle) { 5 + 1 * 62, 180 + 0 * 62, 60, 60 }, "8")) {
			strcat(currOp, "8");
		}
		if (GuiButton((Rectangle) { 5 + 2 * 62, 180 + 0 * 62, 60, 60 }, "9")) {
			strcat(currOp, "9");
		}		
		if (GuiButton((Rectangle) { 5 + 3 * 62, 180 + 2 * 62, 60, 60 }, "+")) {
			strcat(currOp, "+");
		}
		if (GuiButton((Rectangle) { 5 + 3 * 62, 180 + 1 * 62, 60, 60 }, "*")) {
			strcat(currOp, "*");
		}
		if (GuiButton((Rectangle) { 5 + 3 * 62, 180 + 0 * 62, 60, 60 }, "/")) {
			strcat(currOp, "/");
		}
		if (GuiButton((Rectangle) { 5 + 4 * 62, 180 + 0 * 62, 60, 60 }, "^")) {
			strcat(currOp, "^");
		}
		if (GuiButton((Rectangle) { 5 + 4 * 62, 180 + 1 * 62, 60, 60 }, "(")) {
			strcat(currOp, "(");
		}
		if (GuiButton((Rectangle) { 5 + 4 * 62, 180 + 2 * 62, 60, 60 }, ")")) {
			strcat(currOp, ")");
		}
		if (GuiButton((Rectangle) { 5 + 1 * 62, 180 + 3 * 62, 60, 60 }, ".")) {
			strcat(currOp, ".");
		}
		if (GuiButton((Rectangle) { 5 + 4 * 62, 180 + 3 * 62, 60, 60 }, "=")) {
			double sum = evaluate(currOp);
			strcat(currOp, "=");
			strcpy(prevOp, currOp);
			if (sum == NAN) {
				//strcat(currOp, "NAN");
				strcpy(currOp, "NAN");
			}
			else {
				char* temp[100];
				snprintf(temp, 100, "%.4f", sum);
				//strcat(string, itoa(sum, temp, 10));
				//strcat(currOp, temp);
				strcpy(currOp, temp);
			}
		}
		if (GuiButton((Rectangle) { 5 + 2 * 62, 180 + 3 * 62, 60, 60 }, "<-")) {
			//strcat(string, "\b");
			if (strlen(currOp) > 0) {
				currOp[strlen(currOp) - 1] = '\0';
			}
		}
		if (GuiButton((Rectangle) { 5 + 3 * 62, 180 + 3 * 62, 60, 60 }, "C")) {
			currOp[0] = '\0';
		}

		/*bool button = false;
		int x;
		int y;
		for (x = 0; x < 4; x++) {
			for (y = 0; y < 4; y++) {
				char str[12];
				itoa(x + y, str, 10);
				button = GuiButton((Rectangle) {5 + x * 62, 180 + y * 62, 60, 60 }, str);
			}
		}*/

		/*
		if (GuiButton((Rectangle) { 24, 24, 120, 30 }, "#191#Show Message")) showMessageBox = true;

		GuiSpinner((Rectangle) { 170, 124, 120, 20 }, NULL, &spin, -10, 10, false);

		if (showMessageBox){
			int result = GuiMessageBox((Rectangle) { wabV.x + 100, wabV.y, 175, 90},
				"#193#Message Box", "Hi! This is a message!", "L;R;U;D");
			if (result == 0) showMessageBox = false;
			if (result == 1) wabV.x -= 100;
			if (result == 2) wabV.x += 100;

		}
		// draw some text using the default font
		DrawText("Hello Raylib", 200,200,20,BLACK);

		// draw our texture to the screen
		DrawTexture(wabbit, 400, 200, WHITE);

		//rotation += 1.0f;

		DrawTextureEx(wabbit, wabV, rotation, 2, WHITE);
		*/
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

double evaluate(char* expresion) {
	double exp = te_interp(expresion, 0);
	printf("%lf\n", exp);
	/**if (exp == NAN) {
		printf("NAN\n");
		return NAN;
	}*/
	return exp;
}
