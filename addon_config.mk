meta:
	ADDON_NAME = ofxImGuizmo
	ADDON_DESCRIPTION = openFrameworks wrapper for ImGuizmo
	ADDON_AUTHOR = Nariaki Iwatani
	ADDON_TAGS = "ImGui" "dear ImGui" "gizmo" "LibGizmo" "ImGuizmo"
	ADDON_URL = https://github.com/nariakiiwatani/ofxImGuizmo

common:
	ADDON_INCLUDES_EXCLUDE = libs/ImGuizmo/example%
	ADDON_INCLUDES_EXCLUDE += libs/ImGuizmo/bin%
	ADDON_SOURCES_EXCLUDE = libs/ImGuizmo/example%
	ADDON_SOURCES_EXCLUDE += libs/ImGuizmo/bin%
	ADDON_SOURCES_EXCLUDE += libs/ImGuizmo/vcpkg-example%
