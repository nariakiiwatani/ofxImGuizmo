#pragma once

#include "ImGuizmo.h"

namespace ImGuizmo
{
static bool Manipulate(const ofCamera &camera, glm::mat4 &matrix, OPERATION operation, MODE mode, glm::mat4 *delta_matrix=nullptr, const float *snap = nullptr, const float *localBounds = nullptr, const float *boundsSnap = nullptr) {
	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
	auto view = glm::inverse(camera.getGlobalTransformMatrix());
	auto proj = camera.getProjectionMatrix();
	return ImGuizmo::Manipulate(&view[0][0], &proj[0][0], operation, mode, &matrix[0][0], delta_matrix?&((*delta_matrix)[0][0]):nullptr, snap, localBounds, boundsSnap);
}
}
