#ifndef __InputHandler__
#define __InputHandler__

class InputHandler {
	private:
	InputHandler();

	public:
	static InputHandler* Instance();
	static void free();
	bool update();
};

#endif
