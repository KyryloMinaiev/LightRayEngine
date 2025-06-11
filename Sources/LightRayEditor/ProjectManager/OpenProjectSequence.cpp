//
// Created by MrFlyingChip on 08.06.2025.
//

#include "OpenProjectSequence.h"
#include "ProjectManager/ProjectManager.h"
#include "EditorGUI/EditorWindows/ProjectWizardWindow.h"
#include "EditorGUI/EditorWindows/ProjectCreatingWindow.h"
#include "NativeFileDialog.h"

namespace LightRayEngine
{
    OpenProjectSequence::OpenProjectSequence(ProjectManager *projectManager)
            : m_projectManager(projectManager)
    {

    }

    void OpenProjectSequence::StartSequence(const OpenProjectCallback &openProjectCallback)
    {
        m_openProjectCallback = openProjectCallback;
        ProjectData projectData;
//        if (m_projectManager->TryGetLastOpenedProject(projectData) &&
//            m_projectManager->TryOpenProjectByPath(projectData.path))
//        {
//            m_openProjectCallback.Invoke(projectData.path);
//            return;
//        }

        OpenProjectWizardWindow();
    }

    void OpenProjectSequence::OnAddProjectButtonPressed()
    {
        std::string selectedProjectPath;
        NativeFileDialog::OpenFolderDialog("", selectedProjectPath);
        m_projectManager->TryAddProjectByPath(selectedProjectPath);
        m_projectWizardWindow->UpdateProjectList(m_projectManager->GetSavedProjects());
    }

    void OpenProjectSequence::OpenProjectWizardWindow()
    {
        ProjectWizardWindow::Create({
                                            CreateAction(this, &OpenProjectSequence::OnAddProjectButtonPressed),
                                            CreateAction(this, &OpenProjectSequence::OnOpenProjectButtonPressed),
                                            CreateAction(this, &OpenProjectSequence::OnRemovedProjectButtonPressed),
                                            CreateAction(this, &OpenProjectSequence::OpenProjectCreatingWindow),
                                    });
    }

    void OpenProjectSequence::OpenProjectCreatingWindow()
    {

    }

    void OpenProjectSequence::OnOpenProjectButtonPressed(const std::string &path)
    {

    }

    void OpenProjectSequence::OnRemovedProjectButtonPressed(const std::string &path)
    {

    }
}
