#pragma once

#include "ofxImGui.h"
#include "ImGuizmo.h"
#include "ofCamera.h"
#include "ofNode.h"
#include <glm/gtx/matrix_decompose.hpp>
#include "imgui_internal.h"

namespace {
static void applyLocalTransformMatrix(ofNode &node, const glm::mat4 &mat) {
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(mat, scale, rotation, translation, skew, perspective);
	
	node.setPosition(translation);
	node.setOrientation(rotation);
	node.setScale(scale);
}
static void applyWorldTransformMatrix(ofNode &node, const glm::mat4 &mat) {
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(mat, scale, rotation, translation, skew, perspective);
	
	node.setGlobalPosition(translation);
	node.setGlobalOrientation(rotation);
	node.setScale(scale/(node.getParent()?node.getParent()->getGlobalScale():glm::vec3{1,1,1}));
}
static ofRectangle getViewport(const ofCamera &cam) {
	class MyCamera : public ofCamera {
	public:
		MyCamera(const ofCamera &cam):ofCamera(cam){}
		using ofCamera::getViewport;
	};
	return MyCamera(cam).getViewport();
}
}

namespace ImGuizmo
{
static bool Manipulate(const ofCamera &camera, glm::mat4 &matrix, OPERATION operation, MODE mode, const ofRectangle *viewvolume=nullptr, glm::mat4 *delta_matrix=nullptr, const float *snap = nullptr, const float *localBounds = nullptr, const float *boundsSnap = nullptr) {
	auto viewport = viewvolume ? *viewvolume : getViewport(camera);
	ImGuizmo::SetRect(viewport.x, viewport.y, viewport.width, viewport.height);
	auto view = glm::inverse(camera.getGlobalTransformMatrix());
	auto proj = camera.getProjectionMatrix(viewport);
	ImGuizmo::SetOrthographic(camera.getOrtho());
	return ImGuizmo::Manipulate(&view[0][0], &proj[0][0], operation, mode, &matrix[0][0], delta_matrix?&((*delta_matrix)[0][0]):nullptr, snap, localBounds, boundsSnap);
}
static bool Manipulate(const ofCamera &camera, ofNode &node, OPERATION operation, MODE mode, const ofRectangle *viewvolume=nullptr, glm::mat4 *delta_matrix=nullptr, const float *snap = nullptr, const float *localBounds = nullptr, const float *boundsSnap = nullptr) {
	auto matrix = node.getGlobalTransformMatrix();
	if(Manipulate(camera, matrix, operation, mode, viewvolume, delta_matrix, snap, localBounds, boundsSnap)) {
		applyWorldTransformMatrix(node, matrix);
		return true;
	}
	return false;
}
static bool ViewManipulate(ofNode &node, float eye_length, const ofRectangle &pos_size, const ofColor &bg_color) {
	auto view = glm::inverse(node.getGlobalTransformMatrix());
	auto view_cache = view;
	auto colorToHex = [](const ofColor &color) -> ImU32 {
		return color.a<<24|color.getHex();
	};
	ViewManipulate(&view[0][0], eye_length, ImVec2(pos_size.x, pos_size.y), ImVec2(pos_size.width, pos_size.height), colorToHex(bg_color));
	if(view != view_cache) {
		applyLocalTransformMatrix(node, glm::inverse(view));
		return true;
	}
	return false;
}
}
