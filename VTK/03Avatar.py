import vtkmodules.vtkRenderingOpenGL2
from vtkmodules.vtkInteractionStyle import vtkInteractorStyleTrackballCamera
from vtkmodules.vtkCommonColor import vtkNamedColors
from vtkmodules.vtkCommonTransforms import vtkTransform
from vtkmodules.vtkFiltersSources import vtkCubeSource, vtkSphereSource, vtkConeSource, vtkCylinderSource
from vtkmodules.vtkRenderingCore import vtkActor, vtkPolyDataMapper, vtkRenderWindow, vtkRenderWindowInteractor, vtkRenderer
import time

def transform(transformation, translate=(0.0, 0.0, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0)):
    transformation.Translate(translate)
    transformation.RotateZ(rotate[2])
    transformation.RotateY(rotate[1])
    transformation.RotateX(rotate[0])
    transformation.Scale(scale)
    return transformation

def create_jointActor(radius=0.25, color=(0.5, 0.5, 0.5), transform=None):
    source = vtkSphereSource()
    source.SetRadius(radius)
    mapper = vtkPolyDataMapper()
    mapper.SetInputConnection(source.GetOutputPort())
    actor = vtkActor()
    actor.SetMapper(mapper)
    if transform:
        actor.SetUserTransform(transform)
    actor.GetProperty().SetColor(color)
    return actor

def create_bodyActor(radius=0.25, height=0.5, resolution=100, color=(0.5, 0.5, 0.5), transform=None):
    source = vtkCylinderSource()
    source.SetRadius(radius)
    source.SetHeight(height)
    source.SetResolution(resolution)
    mapper = vtkPolyDataMapper()
    mapper.SetInputConnection(source.GetOutputPort())
    actor = vtkActor()
    actor.SetMapper(mapper)
    if transform:
        actor.SetUserTransform(transform)
    actor.GetProperty().SetColor(color)
    return actor

def create_cubeActor(xlength=0.35, ylength=0.1, zlength=0.5, color=(1.0, 1.0, 0.0), transform=None):
    source = vtkCubeSource()
    source.SetXLength(xlength)
    source.SetYLength(ylength)
    source.SetZLength(zlength)
    mapper = vtkPolyDataMapper()
    mapper.SetInputConnection(source.GetOutputPort())
    actor = vtkActor()
    actor.SetMapper(mapper)
    if transform:
        actor.SetUserTransform(transform)
    actor.GetProperty().SetColor(color)
    return actor

def main(argv):
    #####################################################################################################################
    ####################################################### Pelvis ######################################################
    #####################################################################################################################
    ## Spine ##
    # Pelvis Joint
    pelvTransform = vtkTransform()
    pelvTransform = transform(pelvTransform, translate=(0.0, 0.0, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    pelvActor = create_jointActor(0.25, color=(1.0, 0.0, 0.0), transform=pelvTransform)

    # Pelvis to Hip
    pelv2LeftHipTransform = vtkTransform()
    pelv2LeftHipTransform = transform(pelv2LeftHipTransform, translate=(0.25, -0.25, 0.0), rotate=(0.0, 0.0, 45.0), scale=(1.0, 1.0, 1.0))
    pelv2LeftHipActor = create_bodyActor(0.1, 0.5, 100, transform=pelv2LeftHipTransform)

    pelv2RightHipTransform = vtkTransform()
    pelv2RightHipTransform = transform(pelv2RightHipTransform, translate=(-0.25, -0.25, 0.0), rotate=(0.0, 0.0, -45.0), scale=(1.0, 1.0, 1.0))
    pelv2RightHipActor = create_bodyActor(0.1, 0.5, 100, transform=pelv2RightHipTransform)

    # Pelvis to Spine1
    pelv2Spine1Transform = vtkTransform()
    pelv2Spine1Transform.SetInput(pelvTransform)
    pelv2Spine1Transform = transform(pelv2Spine1Transform, translate=(0.0, 0.25, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    pelv2Spine1Actor = create_bodyActor(0.1, 0.5, 100, transform=pelv2Spine1Transform)

    # Spine1 Joint
    spine1Transform = vtkTransform()
    spine1Transform.SetInput(pelvTransform)
    spine1Transform = transform(spine1Transform, translate=(0.0, 0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    spine1Actor = create_jointActor(0.25, transform=spine1Transform)
    
    # Spine1 to Spine2
    spine12spine2Transform = vtkTransform()
    spine12spine2Transform.SetInput(spine1Transform)
    spine12spine2Transform = transform(spine12spine2Transform, translate=(0.0, 0.25, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    spine12spine2Actor = create_bodyActor(0.1, 0.5, 100, transform=spine12spine2Transform)

    # Spine2 Joint
    spine2Transform = vtkTransform()
    spine2Transform.SetInput(spine1Transform)
    spine2Transform = transform(spine2Transform, translate=(0.0, 0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    spine2Actor = create_jointActor(0.25, transform=spine2Transform)
    
    # Spine2 to Spine3
    spine22spine3Transform = vtkTransform()
    spine22spine3Transform.SetInput(spine2Transform)
    spine22spine3Transform = transform(spine22spine3Transform, translate=(0.0, 0.25, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    spine22spine3Actor = create_bodyActor(0.1, 0.5, 100, transform=spine22spine3Transform)
    
    # Spine3 Joint
    spine3Transform = vtkTransform()
    spine3Transform.SetInput(spine2Transform)
    spine3Transform = transform(spine3Transform, translate=(0.0, 0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    spine3Actor = create_jointActor(0.25, transform=spine3Transform)
    
    # Spine3 to Collar
    spine32LeftCollarTransform = vtkTransform()
    spine32LeftCollarTransform = transform(spine32LeftCollarTransform, translate=(0.25, 1.75, 0.0), rotate=(0.0, 0.0, -45.0), scale=(1.0, 1.0, 1.0))
    spine32LeftCollarActor = create_bodyActor(0.1, 0.5, 100, transform=spine32LeftCollarTransform)
    
    spine32RightCollarTransform = vtkTransform()
    spine32RightCollarTransform = transform(spine32RightCollarTransform, translate=(-0.25, 1.75, 0.0), rotate=(0.0, 0.0, 45.0), scale=(1.0, 1.0, 1.0))
    spine32RightCollarActor = create_bodyActor(0.1, 0.5, 100, transform=spine32RightCollarTransform)
    
    # Collar Joint
    leftCollarTransform = vtkTransform()
    leftCollarTransform.SetInput(spine3Transform)
    leftCollarTransform = transform(leftCollarTransform, translate=(0.5, 0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    leftCollarActor = create_jointActor(0.25, transform=leftCollarTransform)
    
    rightCollarTransform = vtkTransform()
    rightCollarTransform.SetInput(spine3Transform)
    rightCollarTransform = transform(rightCollarTransform, translate=(-0.5, 0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    rightCollarActor = create_jointActor(0.25, transform=rightCollarTransform)
    
    # Collar to Shoulder
    leftCollar2LeftShoulderTransform = vtkTransform()
    leftCollar2LeftShoulderTransform = transform(leftCollar2LeftShoulderTransform, translate=(0.75, 2.25, 0.0), rotate=(0.0, 0.0, -45.0), scale=(1.0, 1.0, 1.0))
    leftCollar2LeftShoulderActor = create_bodyActor(0.1, 0.75, 100, transform=leftCollar2LeftShoulderTransform)
    
    rightCollar2RightShoulderTransform = vtkTransform()
    rightCollar2RightShoulderTransform = transform(rightCollar2RightShoulderTransform, translate=(-0.75, 2.25, 0.0), rotate=(0.0, 0.0, 45.0), scale=(1.0, 1.0, 1.0))
    rightCollar2RightShoulderActor = create_bodyActor(0.1, 0.75, 100, transform=rightCollar2RightShoulderTransform)
    
    # Neck Joint
    neckTransform = vtkTransform()
    neckTransform.SetInput(spine3Transform)
    neckTransform = transform(neckTransform, translate=(0.0, 1.25, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    neckActor = create_jointActor(0.25, transform=neckTransform)
    
    # Neck to Head
    neck2HeadTransform = vtkTransform()
    neck2HeadTransform.SetInput(neckTransform)
    neck2HeadTransform = transform(neck2HeadTransform, translate=(0.0, 0.45, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    neck2HeadActor = create_bodyActor(0.1, 0.5, 100, transform=neck2HeadTransform)
    
    # Neck to Shoulder
    neck2LeftShoulderTransform = vtkTransform()
    neck2LeftShoulderTransform = transform(neck2LeftShoulderTransform, translate=(0.5, 2.65, 0.0), rotate=(0.0, 0.0, 75.0), scale=(1.0, 1.0, 1.0))
    neck2LeftShoulderActor = create_bodyActor(0.1, 1.0, 100, transform=neck2LeftShoulderTransform)
    
    neck2RightShoulderTransform = vtkTransform()
    neck2RightShoulderTransform = transform(neck2RightShoulderTransform, translate=(-0.5, 2.65, 0.0), rotate=(0.0, 0.0, -75.0), scale=(1.0, 1.0, 1.0))
    neck2RightShoulderActor = create_bodyActor(0.1, 1.0, 100, transform=neck2RightShoulderTransform)
    
    # Head
    headTransform = vtkTransform()
    headTransform.SetInput(neck2HeadTransform)
    headTransform = transform(headTransform, translate=(0.0, 0.35, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    headActor = create_jointActor(0.5, color=(1.0, 1.0, 1.0), transform=headTransform)

    #####################################################################################################################
    ##################################################### Left Arm ######################################################
    #####################################################################################################################
    # Shoulder Joint
    leftShoulderTransform = vtkTransform()
    leftShoulderTransform = transform(leftShoulderTransform, translate=(1.0, 2.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    leftShoulderActor = create_jointActor(0.25, color=(0.0, 0.25, 0.75), transform=leftShoulderTransform)
    
    # Upper Arm
    leftUpperArmTransform = vtkTransform()
    leftUpperArmTransform.SetInput(leftShoulderTransform)
    leftUpperArmTransform = transform(leftUpperArmTransform, translate=(0.5, 0.0, 0.0), rotate=(0.0, 0.0, 90.0), scale=(1.0, 1.0, 1.0))
    leftUpperArmActor = create_bodyActor(0.1, 0.75, 100, color=(0.0, 0.25, 0.75), transform=leftUpperArmTransform)
    
    # Elbow Joint
    leftElbowTransform = vtkTransform()
    leftElbowTransform.SetInput(leftUpperArmTransform)
    leftElbowTransform = transform(leftElbowTransform, translate=(0.0, -0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    leftElbowActor = create_jointActor(0.25, color=(0.0, 0.25, 0.75), transform=leftElbowTransform)
    
    # Lower Arm
    leftLowerArmTransform = vtkTransform()
    leftLowerArmTransform.SetInput(leftElbowTransform)
    leftLowerArmTransform = transform(leftLowerArmTransform, translate=(0.0, -0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    leftLowerArmActor = create_bodyActor(0.1, 0.75, 100, color=(0.0, 0.25, 0.75), transform=leftLowerArmTransform)
    
    # Wrist Joint
    leftWristTransform = vtkTransform()
    leftWristTransform.SetInput(leftLowerArmTransform)
    leftWristTransform = transform(leftWristTransform, translate=(0.0, -0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    leftWristActor = create_jointActor(0.25, color=(0.0, 0.25, 0.75), transform=leftWristTransform)
    
    # Hand
    leftHandTransform = vtkTransform()
    leftHandTransform.SetInput(leftWristTransform)
    leftHandTransform = transform(leftHandTransform, translate=(0.0, -0.25, 0.0), rotate=(90.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    leftHandActor = create_cubeActor(0.35, 0.1, 0.5, color=(1.0, 1.0, 0.0), transform=leftHandTransform)
    
    #####################################################################################################################
    ##################################################### Right Arm ######################################################
    #####################################################################################################################
    # Shoulder Joint
    rightShoulderTransform = vtkTransform()
    rightShoulderTransform = transform(rightShoulderTransform, translate=(-1.0, 2.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    rightShoulderActor = create_jointActor(0.25, color=(0.0, 0.25, 0.75), transform=rightShoulderTransform)
    
    # Upper Arm
    rightUpperArmTransform = vtkTransform()
    rightUpperArmTransform.SetInput(rightShoulderTransform)
    rightUpperArmTransform = transform(rightUpperArmTransform, translate=(-0.5, 0.0, 0.0), rotate=(0.0, 0.0, -90.0), scale=(1.0, 1.0, 1.0))
    rightUpperArmActor = create_bodyActor(0.1, 0.75, 100, color=(0.0, 0.25, 0.75), transform=rightUpperArmTransform)
    
    # Elbow Joint
    rightElbowTransform = vtkTransform()
    rightElbowTransform.SetInput(rightUpperArmTransform)
    rightElbowTransform = transform(rightElbowTransform, translate=(0.0, -0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    rightElbowActor = create_jointActor(0.25, color=(0.0, 0.25, 0.75), transform=rightElbowTransform)
    
    # Lower Arm
    rightLowerArmTransform = vtkTransform()
    rightLowerArmTransform.SetInput(rightElbowTransform)
    rightLowerArmTransform = transform(rightLowerArmTransform, translate=(0.0, -0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    rightLowerArmActor = create_bodyActor(0.1, 0.75, 100, color=(0.0, 0.25, 0.75), transform=rightLowerArmTransform)
    
    # Wrist Joint
    rightWristTransform = vtkTransform()
    rightWristTransform.SetInput(rightLowerArmTransform)
    rightWristTransform = transform(rightWristTransform, translate=(0.0, -0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    rightWristActor = create_jointActor(0.25, color=(0.0, 0.25, 0.75), transform=rightWristTransform)
    
    # Hand
    rightHandTransform = vtkTransform()
    rightHandTransform.SetInput(rightWristTransform)
    rightHandTransform = transform(rightHandTransform, translate=(0.0, -0.25, 0.0), rotate=(90.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    rightHandActor = create_cubeActor(0.35, 0.1, 0.5, color=(1.0, 1.0, 0.0), transform=rightHandTransform)

    #####################################################################################################################
    ##################################################### Left Leg ######################################################
    #####################################################################################################################
    # Hip Joint
    leftHipTransform = vtkTransform()
    leftHipTransform = transform(leftHipTransform, translate=(0.5, -0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    leftHipActor = create_jointActor(0.25, color=(0.0, 0.75, 0.25), transform=leftHipTransform)

    # Upper Leg
    leftUpperLegTransform = vtkTransform()
    leftUpperLegTransform.SetInput(leftHipTransform)
    leftUpperLegTransform = transform(leftUpperLegTransform, translate=(0.0, -0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))    
    leftUpperLegActor = create_bodyActor(0.1, 1.0, 100, color=(0.0, 0.75, 0.25), transform=leftUpperLegTransform)

    # Knee Joint
    leftKneeTransform = vtkTransform()
    leftKneeTransform.SetInput(leftUpperLegTransform)
    leftKneeTransform = transform(leftKneeTransform, translate=(0.0, -0.75, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    leftKneeActor = create_jointActor(0.25, color=(0.0, 0.75, 0.25), transform=leftKneeTransform)
    
    # Lower Leg
    leftLowerLegTransform = vtkTransform()
    leftLowerLegTransform.SetInput(leftKneeTransform)
    leftLowerLegTransform = transform(leftLowerLegTransform, translate=(0.0, -0.75, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    leftLowerLegActor = create_bodyActor(0.1, 1.0, 100, color=(0.0, 0.75, 0.25), transform=leftLowerLegTransform)
    
    # Ankle Joint
    leftAnkleTransform = vtkTransform()
    leftAnkleTransform.SetInput(leftLowerLegTransform)
    leftAnkleTransform = transform(leftAnkleTransform, translate=(0.0, -0.75, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    leftAnkleActor = create_jointActor(0.25, color=(0.0, 0.75, 0.25), transform=leftAnkleTransform)
    
    # Foot
    leftFootTransform = vtkTransform()
    leftFootTransform.SetInput(leftAnkleTransform)
    leftFootTransform = transform(leftFootTransform, translate=(0.0, -0.25, 0.25), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    leftFootActor = create_cubeActor(0.35, 0.1, 0.5, color=(1.0, 1.0, 0.0), transform=leftFootTransform)

    #####################################################################################################################
    ##################################################### Right Leg ######################################################
    #####################################################################################################################
    # Hip Joint
    rightHipTransform = vtkTransform()
    rightHipTransform = transform(rightHipTransform, translate=(-0.5, -0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    rightHipActor = create_jointActor(0.25, color=(0.0, 0.75, 0.25), transform=rightHipTransform)

    # Upper Leg
    rightUpperLegTransform = vtkTransform()
    rightUpperLegTransform.SetInput(rightHipTransform)
    rightUpperLegTransform = transform(rightUpperLegTransform, translate=(0.0, -0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))    
    rightUpperLegActor = create_bodyActor(0.1, 1.0, 100, color=(0.0, 0.75, 0.25), transform=rightUpperLegTransform)

    # Knee Joint
    rightKneeTransform = vtkTransform()
    rightKneeTransform.SetInput(rightUpperLegTransform)
    rightKneeTransform = transform(rightKneeTransform, translate=(0.0, -0.75, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    rightKneeActor = create_jointActor(0.25, color=(0.0, 0.75, 0.25), transform=rightKneeTransform)
    
    # Lower Leg
    rightLowerLegTransform = vtkTransform()
    rightLowerLegTransform.SetInput(rightKneeTransform)
    rightLowerLegTransform = transform(rightLowerLegTransform, translate=(0.0, -0.75, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    rightLowerLegActor = create_bodyActor(0.1, 1.0, 100, color=(0.0, 0.75, 0.25), transform=rightLowerLegTransform)
    
    # Ankle Joint
    rightAnkleTransform = vtkTransform()
    rightAnkleTransform.SetInput(rightLowerLegTransform)
    rightAnkleTransform = transform(rightAnkleTransform, translate=(0.0, -0.75, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    rightAnkleActor = create_jointActor(0.25, color=(0.0, 0.75, 0.25), transform=rightAnkleTransform)
    
    # Foot
    rightFootTransform = vtkTransform()
    rightFootTransform.SetInput(rightAnkleTransform)
    rightFootTransform = transform(rightFootTransform, translate=(0.0, -0.25, 0.25), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    rightFootActor = create_cubeActor(0.35, 0.1, 0.5, color=(1.0, 1.0, 0.0), transform=rightFootTransform)

    #####################################################################################################################
    ###################################################### Render #######################################################
    #####################################################################################################################
    colors = vtkNamedColors()
    renderer = vtkRenderer()
    renderer.SetBackground(colors.GetColor3d('SlateGray'))
    
    # Add Actors (Pelvis)
    renderer.AddActor(pelvActor)
    renderer.AddActor(pelv2LeftHipActor)
    renderer.AddActor(pelv2RightHipActor)
    renderer.AddActor(pelv2Spine1Actor)
    renderer.AddActor(spine1Actor)
    renderer.AddActor(spine12spine2Actor)
    renderer.AddActor(spine2Actor)
    renderer.AddActor(spine22spine3Actor)
    renderer.AddActor(spine3Actor)
    renderer.AddActor(spine32LeftCollarActor)
    renderer.AddActor(spine32RightCollarActor)
    renderer.AddActor(leftCollarActor)
    renderer.AddActor(rightCollarActor)
    renderer.AddActor(leftCollar2LeftShoulderActor)
    renderer.AddActor(rightCollar2RightShoulderActor)
    renderer.AddActor(neckActor)
    renderer.AddActor(neck2HeadActor)
    renderer.AddActor(neck2LeftShoulderActor)
    renderer.AddActor(neck2RightShoulderActor)
    renderer.AddActor(headActor)

    # Add Actors (Left Arm)
    renderer.AddActor(leftShoulderActor)
    renderer.AddActor(leftUpperArmActor)
    renderer.AddActor(leftElbowActor)
    renderer.AddActor(leftLowerArmActor)
    renderer.AddActor(leftWristActor)
    renderer.AddActor(leftHandActor)
    
    # Add Actors (Right Arm)
    renderer.AddActor(rightShoulderActor)
    renderer.AddActor(rightUpperArmActor)
    renderer.AddActor(rightElbowActor)
    renderer.AddActor(rightLowerArmActor)
    renderer.AddActor(rightWristActor)
    renderer.AddActor(rightHandActor)

    # Add Actors (Left Leg)
    renderer.AddActor(leftHipActor)
    renderer.AddActor(leftUpperLegActor)
    renderer.AddActor(leftKneeActor)
    renderer.AddActor(leftLowerLegActor)
    renderer.AddActor(leftAnkleActor)
    renderer.AddActor(leftFootActor)
    
    # Add Actors (Right Leg)
    renderer.AddActor(rightHipActor)
    renderer.AddActor(rightUpperLegActor)
    renderer.AddActor(rightKneeActor)
    renderer.AddActor(rightLowerLegActor)
    renderer.AddActor(rightAnkleActor)
    renderer.AddActor(rightFootActor)
    
    renderWindow = vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindow.SetSize(500, 700)
    renderWindow.SetWindowName('Full_Human_Model_T_Pose')
    interactor = vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)
    style = vtkInteractorStyleTrackballCamera()
    interactor.SetInteractorStyle(style)
    renderWindow.Render()
    
    for angle in range(0, 25, 5):
        leftHipTransform.RotateX(angle)
        rightHipTransform.RotateX(-angle)
        renderWindow.Render()
        time.sleep(0.1)
        
    for angle in range(0, 10, 2):
        leftKneeTransform.RotateX(angle)
        rightKneeTransform.RotateX(angle)
        renderWindow.Render()
        time.sleep(0.1)
        
    for angle in range(0, 30, 5):
        leftShoulderTransform.RotateY(-angle)
        leftElbowTransform.RotateZ(angle)
        rightShoulderTransform.RotateY(-angle)
        rightElbowTransform.RotateZ(angle)
        
        renderWindow.Render()
        time.sleep(0.1)
    
    interactor.Initialize()
    interactor.Start()
    
    
class vtkMyCallback(object):
    """
    Callback for the interaction.
    """
    
    def __call__(self, caller, ev):
        t = vtkTransform()
        widget = caller
        widget.GetTransform(t)
        widget.GetProp3D().SetUserTransform(t)
    
    
if __name__ == '__main__':
    import sys
    main(sys.argv)