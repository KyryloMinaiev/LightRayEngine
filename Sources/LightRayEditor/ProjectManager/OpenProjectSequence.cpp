//
// Created by MrFlyingChip on 08.06.2025.
//

#include "OpenProjectSequence.h"
#include "ProjectManager/ProjectManager.h"
#include "EditorGUI/EditorWindows/ProjectWizardWindow.h"
#include "EditorGUI/EditorWindows/ProjectCreatingWindow.h"
#include "NativeFileDialog.h"
#include "ProjectCreatingService.h"

namespace LightRayEngine
{
    OpenProjectSequence::OpenProjectSequence(ProjectManager *projectManager)
            : m_projectManager(projectManager), m_projectWizardWindow(nullptr), m_projectCreatingWindow(nullptr),
              m_projectCreatingService(projectManager)
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
        ReloadProjectWizardWindow();
    }

    void OpenProjectSequence::OpenProjectWizardWindow()
    {
        m_projectWizardWindow = ProjectWizardWindow::Create({
                                                                    CreateAction(this,
                                                                                 &OpenProjectSequence::OnAddProjectButtonPressed),
                                                                    CreateAction(this,
                                                                                 &OpenProjectSequence::OnOpenProjectButtonPressed),
                                                                    CreateAction(this,
                                                                                 &OpenProjectSequence::OnRemovedProjectButtonPressed),
                                                                    CreateAction(this,
                                                                                 &OpenProjectSequence::OpenProjectCreatingWindow),
                                                            });
        ReloadProjectWizardWindow();
    }

    void OpenProjectSequence::OpenProjectCreatingWindow()
    {
        m_projectCreatingWindow = ProjectCreatingWindow::Create(
                CreateAction(this, &OpenProjectSequence::OnCreateProjectButtonPressed),
                CreateDelegate(&m_projectCreatingService, &ProjectCreatingService::ValidatePathForProjectCreating));
    }

    void OpenProjectSequence::OnOpenProjectButtonPressed(const std::string &path)
    {
        m_projectWizardWindow->Close();
    }

    void OpenProjectSequence::OnRemovedProjectButtonPressed(const std::string &path)
    {
        m_projectManager->RemoveProjectFromList(path);
        ReloadProjectWizardWindow();
    }

    void OpenProjectSequence::ReloadProjectWizardWindow()
    {
        m_projectWizardWindow->UpdateProjectList(m_projectManager->GetSavedProjects());
    }

    void OpenProjectSequence::OnCreateProjectButtonPressed(const std::string &path, const std::string &name)
    {
        if (m_projectCreatingService.TryCreateProjectByPath(path, name))
        {
            m_projectCreatingWindow->Close();
            ReloadProjectWizardWindow();
            return;
        }
    }
}
