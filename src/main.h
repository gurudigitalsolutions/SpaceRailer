void handleRender();
void handleReshape(GLint newWidth, GLint newHeight);
void handleIdle();
void init();

extern short windowWidth;
extern short windowHeight;

enum programMode { PROGRAM_BOOT, PROGRAM_MAINMENU, PROGRAM_GAME };
