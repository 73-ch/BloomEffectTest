#pragma once

#include "ofMain.h"

#define SAMPLE_COUNT 15

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	ofEasyCam cam;

	glm::vec3 light_direction;

	ofShader light_shader;
	ofShader extract_shader;
	ofShader bloom_shader;
	ofShader blend_shader;

	ofFbo default_fbo;
	ofFbo dst_fbo;
	ofFbo src_fbo;
	
	vector<float> offset_h{-0.00419999985024333, -0.003599999938160181, -0.003000000026077032, -0.002400000113993883, -0.0017999999690800905, -0.0012000000569969416, -0.0006000000284984708, 0, 0.0006000000284984708, 0.0012000000569969416, 0.0017999999690800905, 0.002400000113993883, 0.003000000026077032, 0.003599999938160181, 0.00419999985024333};
	vector<float> weight_h{0.06666630266736337, 0.06666645866669414, 0.06666659066641296, 0.06666669866637732, 0.06666678266647057, 0.06666684266660196, 0.06666687866670673, 0.06666689066674597, 0.06666687866670673, 0.06666684266660196, 0.06666678266647057, 0.06666669866637732, 0.06666659066641296, 0.06666645866669414, 0.06666630266736337};
	vector<float> offset_v{-0.00419999985024333,-0.003599999938160181,-0.003000000026077032,-0.002400000113993883,-0.0017999999690800905,-0.0012000000569969416,-0.0006000000284984708,0,0.0006000000284984708,0.0012000000569969416,0.0017999999690800905,0.002400000113993883,0.003000000026077032,0.003599999938160181,0.00419999985024333};
	vector<float> weight_v{0.06666630266736337, 0.06666645866669414, 0.06666659066641296, 0.06666669866637732, 0.06666678266647057, 0.06666684266660196, 0.06666687866670673, 0.06666689066674597, 0.06666687866670673, 0.06666684266660196, 0.06666678266647057, 0.06666669866637732, 0.06666659066641296, 0.06666645866669414, 0.06666630266736337};		

	bool enable = false;
};
