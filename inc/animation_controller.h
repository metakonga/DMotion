#ifndef ANIMATION_CONTROLLER
#define ANIMATION_CONTROLLER

class animation_controller
{
public:
	animation_controller(){}
	~animation_controller(){}

	static void setTotalFrame(int _totalFrame) { totalFrame = _totalFrame; }
	static void setPlayEnable(bool isPlay) { _isPlay = isPlay; }
	static int CurrentFrame() { return currentFrame; }
	static int TotalFrame() { return totalFrame; }
	static bool IsPlay() { return _isPlay; }
	static void initFrame() { currentFrame = 0; }
	static void next() 
	{ 
		currentFrame = currentFrame == totalFrame ? currentFrame : currentFrame + 1;  
	}
	static void previous() 
	{ 
		currentFrame = currentFrame == 0 ? currentFrame : currentFrame - 1; 
	}
	static void next2x() 
	{
		currentFrame = currentFrame >= totalFrame ? totalFrame : currentFrame + 2;
	}
	static void previous2x() 
	{ 
		currentFrame = currentFrame <= 1 ? currentFrame : currentFrame - 2; 
	}

private:
	static bool _isPlay;
	static int totalFrame;
	static int currentFrame;
};



#endif