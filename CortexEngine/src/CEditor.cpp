#include "include\CEditor.h"

CE::Editor::CEditor::CEditor()
	:m_pEdiCam(nullptr)
{

}

CE::Editor::CEditor::~CEditor()
{
	delete m_pEdiCam;
}
