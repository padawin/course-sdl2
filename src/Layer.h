#ifndef __Layer__
#define __Layer__

class Layer {
	public:
	virtual ~Layer() {}
	virtual void render() = 0;
	virtual void update() = 0;
};

#endif
