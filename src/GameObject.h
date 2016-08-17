#ifndef __GameObject__
#define __GameObject__

class GameObject {
	public:
	virtual ~GameObject() {}

	/**
	 * An object can be updated
	 */
	virtual void update() = 0;
};

class GameObjectLoader {

};
#endif
