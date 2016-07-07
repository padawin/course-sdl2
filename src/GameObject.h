class GameObject {
	private:
	int m_iX;
	int m_iY;
	int m_iWidth;
	int m_iHeight;

	public:
	void load(const int x, const int y, const int width, const int height);
	void update();
	void render();
	void clean();
};
