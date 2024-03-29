#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    ofSetBackgroundColor(0);

    light_shader.load("shaders/default.vert", "shaders/light.frag");

    extract_shader.load("shaders/fboplane.vert", "shaders/extract.frag");
    blur_shader.load("shaders/fboplane.vert", "shaders/blur.frag");
    blend_shader.load("shaders/fboplane.vert", "shaders/blend.frag");

    light_direction = glm::vec3(-0.5, 1.0, 0.5);
    windowResized(ofGetWidth(), ofGetHeight());


    box.set(100);

    box.enableColors();
    auto &m = box.getMesh();
    vector<ofFloatColor> colors(m.getNumVertices(), ofFloatColor(0.2, 0.5,0.5,1.0));
    m.addColors(colors);

    
}

//--------------------------------------------------------------
void ofApp::update(){
    // light_direction = glm::vec3(cos(ofGetElapsedTimef() * 0.5), 0.5, sin(ofGetElapsedTimef() * 0.5));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    default_fbo.begin();
    ofClear(0);

    cam.begin();

    light_shader.begin();

    light_shader.setUniformMatrix4f("inv_matrix", glm::inverse(cam.getModelViewProjectionMatrix()));
    light_shader.setUniform3f("light_direction", -light_direction);
    light_shader.setUniform3f("eye_direction", cam.getGlobalPosition());
    light_shader.setUniform4f("ambient_color", glm::vec4(0.,0.1,0.1,1.0));

    ofSetColor(255, 200);
    box.draw();

    light_shader.end();

    cam.end();

    default_fbo.end();
    ofPopMatrix();

    


    dst_fbo.begin();
    ofClear(0);
    extract_shader.begin();

    extract_shader.setUniform1f("min_bright", 0.5);
    extract_shader.setUniformTexture("input_texture", default_fbo.getTexture(), 0);

    extract_shader.setUniform2f("u_resolution", glm::vec2(src_fbo.getWidth(), src_fbo.getHeight()));
    ofDrawPlane(0, 0, dst_fbo.getWidth() * 2., dst_fbo.getWidth() * 2.);

    extract_shader.end();
    dst_fbo.end();

    swap(dst_fbo, src_fbo);
    
    for (int i = 0; i < blur_count; i++) {
        // 縦方向のぼかし
        dst_fbo.begin();
        ofClear(0);
        blur_shader.begin();
        blur_shader.setUniform2f("u_resolution", glm::vec2(src_fbo.getWidth(), src_fbo.getHeight()));

        // blur_shader.setUniform1fv("offsets_v", &offset_v[0], offset_v.size());
        // blur_shader.setUniform1fv("weights_v", &weight_v[0], weight_v.size());
        
        blur_shader.setUniformTexture("input_texture", src_fbo.getTexture(), 0);
        blur_shader.setUniform1i("is_vertical", true);

        ofDrawPlane(0, 0, dst_fbo.getWidth() * 2., dst_fbo.getWidth() * 2.);

        dst_fbo.end();

        swap(dst_fbo, src_fbo);

        // 横方向へのぼかし
        dst_fbo.begin();
        ofClear(0);

        blur_shader.setUniform1fv("offsets_h", &offset_h[0], offset_h.size());
        blur_shader.setUniform1fv("weights_h", &weight_h[0], weight_h.size());

        blur_shader.setUniformTexture("input_texture", src_fbo.getTexture(), 0);
        blur_shader.setUniform1i("is_vertical", false);

        ofDrawPlane(0, 0, dst_fbo.getWidth() * 2., dst_fbo.getWidth() * 2.);

        blur_shader.end();
        dst_fbo.end();

        swap(dst_fbo, src_fbo);
    }
   

    // 最終的に元のシーンと加算合成

    if (enable) {
        blend_shader.begin();

        blend_shader.setUniform2f("u_resolution", glm::vec2(ofGetWidth(), ofGetHeight()));
        blend_shader.setUniformTexture("input1", default_fbo, 0);
        
        blend_shader.setUniformTexture("input2", src_fbo, 1);    
        

        ofDrawPlane(0, 0, ofGetWidth() * 2., ofGetHeight() * 2.);

        blend_shader.end();

    } else {
        default_fbo.draw(0,0);
    }

    // src_fbo.draw(0,0,ofGetWidth() / 6, ofGetHeight() / 6.);
    

    // fbo.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_F1) {
        enable = !enable;

        ofLogNotice() << enable;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    ofDisableArbTex();
    ofFboSettings settings;
    settings.width = ofGetWidth();
    settings.height = ofGetHeight();
    settings.maxFilter = GL_LINEAR;
    settings.minFilter = GL_LINEAR;
    settings.internalformat = GL_RGBA;

    dst_fbo.allocate(ofGetWidth() / shrink_size, ofGetHeight() / shrink_size);
    src_fbo.allocate(ofGetWidth() / shrink_size , ofGetHeight() / shrink_size);
    dst_fbo.getTexture().getTextureData().bFlipTexture = true;
    src_fbo.getTexture().getTextureData().bFlipTexture = true;

    dst_fbo.getTexture().setTextureMinMagFilter(GL_LINEAR, GL_LINEAR);
    src_fbo.getTexture().setTextureMinMagFilter(GL_LINEAR, GL_LINEAR);

    default_fbo.allocate(ofGetWidth(), ofGetHeight());
    default_fbo.getTexture().getTextureData().bFlipTexture = true;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
