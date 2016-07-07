class GameObject {
	private:
	int m_iX;
	int m_iY;
	int m_iWidth;
	int m_iHeight;

	public:
	void update();
	void render();
	void clean();
};
