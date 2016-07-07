#include <string>

class GameObject {
	private:
	std::string m_sTextureID;
	int m_iNbFrames;
	int m_iCurrentFrame;
	int m_iCurrentRow;
	int m_iX;
	int m_iY;
	int m_iWidth;
	int m_iHeight;

	public:
	void load(const int x, const int y, const int width, const int height);
	void setTexture(const std::string textureID, int nbFrames);
	void update();
	void render();
	void clean();
};
