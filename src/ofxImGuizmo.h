#pragma once

#include "ImGuizmo.h"
#include "ofNode.h"
#include <glm/gtx/matrix_decompose.hpp>

namespace ImGuizmo
{
static bool Manipulate(const ofCamera &camera, glm::mat4 &matrix, OPERATION operation, MODE mode, glm::mat4 *delta_matrix=nullptr, const float *snap = nullptr, const float *localBounds = nullptr, const float *boundsSnap = nullptr) {
	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
	auto view = glm::inverse(camera.getGlobalTransformMatrix());
	auto proj = camera.getProjectionMatrix();
	return ImGuizmo::Manipulate(&view[0][0], &proj[0][0], operation, mode, &matrix[0][0], delta_matrix?&((*delta_matrix)[0][0]):nullptr, snap, localBounds, boundsSnap);
}
static bool Manipulate(const ofCamera &camera, ofNode &node, OPERATION operation, MODE mode, glm::mat4 *delta_matrix=nullptr, const float *snap = nullptr, const float *localBounds = nullptr, const float *boundsSnap = nullptr) {
	auto matrix = node.getGlobalTransformMatrix();
	if(Manipulate(camera, matrix, operation, mode, delta_matrix, snap, localBounds, boundsSnap)) {
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(matrix, scale, rotation, translation, skew, perspective);
		
		node.setGlobalPosition(translation);
		node.setGlobalOrientation(rotation);
		node.setScale(scale/(node.getParent()?node.getParent()->getGlobalScale():glm::vec3{1,1,1}));
		return true;
	}
	return false;
}
}
