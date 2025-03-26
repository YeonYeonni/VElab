import vtkmodules.vtkRenderingOpenGL2
from vtkmodules.vtkInteractionStyle import vtkInteractorStyleTrackballCamera
from vtkmodules.vtkCommonColor import vtkNamedColors
from vtkmodules.vtkCommonTransforms import vtkTransform
from vtkmodules.vtkCommonDataModel import vtkQuadric
from vtkmodules.vtkFiltersModeling import vtkOutlineFilter
from vtkmodules.vtkImagingCore import vtkExtractVOI
from vtkmodules.vtkImagingHybrid import vtkSampleFunction
from vtkmodules.vtkFiltersSources import vtkCubeSource, vtkSphereSource, vtkCylinderSource
from vtkmodules.vtkFiltersCore import vtkAppendFilter, vtkContourFilter
from vtkmodules.vtkInteractionStyle import vtkInteractorStyleTrackballCamera
from vtkmodules.vtkRenderingCore import vtkActor, vtkPolyDataMapper, vtkRenderWindow, vtkRenderWindowInteractor, vtkRenderer, vtkDataSetMapper


def CreateIsosurface(func, actor, numberOfContours=10):
    # Generate implicit surface.
    contour = vtkContourFilter()
    contour.SetInputConnection(func.GetOutputPort())
    ranges = [1.0, 6.0]
    contour.GenerateValues(numberOfContours, ranges)

    # Map contour
    contourMapper = vtkPolyDataMapper()
    contourMapper.SetInputConnection(contour.GetOutputPort())
    contourMapper.SetScalarRange(0, 7)

    actor.SetMapper(contourMapper)
    return


def CreatePlanes(func, actor, numberOfPlanes):
    #
    # Extract planes from implicit function.
    #

    append = vtkAppendFilter()

    dims = func.GetSampleDimensions()
    sliceIncr = (dims[2] - 1) // (numberOfPlanes + 1)
    sliceNum = -4
    for i in range(0, numberOfPlanes):
        extract = vtkExtractVOI()
        extract.SetInputConnection(func.GetOutputPort())
        extract.SetVOI(0, dims[0] - 1,
                       0, dims[1] - 1,
                       sliceNum + sliceIncr, sliceNum + sliceIncr)
        append.AddInputConnection(extract.GetOutputPort())
        sliceNum += sliceIncr
    append.Update()

    # Map planes
    planesMapper = vtkDataSetMapper()
    planesMapper.SetInputConnection(append.GetOutputPort())
    planesMapper.SetScalarRange(0, 7)

    actor.SetMapper(planesMapper)
    actor.GetProperty().SetAmbient(1.)
    return

# Isosurface
def CreateContours(func, actor, numberOfPlanes, numberOfContours):
    #
    # Extract planes from implicit function
    #

    append = vtkAppendFilter()

    dims = func.GetSampleDimensions()
    sliceIncr = (dims[2] - 1) // (numberOfPlanes + 1)

    sliceNum = -4
    for i in range(0, numberOfPlanes):
        extract = vtkExtractVOI()
        extract.SetInputConnection(func.GetOutputPort())
        extract.SetVOI(0, dims[0] - 1,
                       0, dims[1] - 1,
                       sliceNum + sliceIncr, sliceNum + sliceIncr)
        ranges = [1.0, 6.0]
        contour = vtkContourFilter()
        contour.SetInputConnection(extract.GetOutputPort())
        contour.GenerateValues(numberOfContours, ranges)
        append.AddInputConnection(contour.GetOutputPort())
        sliceNum += sliceIncr
    append.Update()

    # Map planes
    planesMapper = vtkDataSetMapper()
    planesMapper.SetInputConnection(append.GetOutputPort())
    planesMapper.SetScalarRange(0, 7)

    actor.SetMapper(planesMapper)
    actor.GetProperty().SetAmbient(1.)
    return


def CreateOutline(source, actor):
    outline = vtkOutlineFilter()
    outline.SetInputConnection(source.GetOutputPort())
    mapper = vtkPolyDataMapper()
    mapper.SetInputConnection(outline.GetOutputPort())
    actor.SetMapper(mapper)
    return

def transform(translate=(0.0, 0.0, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0)):
    transform = vtkTransform()
    transform.Translate(translate)
    transform.RotateZ(rotate[2])
    transform.RotateY(rotate[1])
    transform.RotateX(rotate[0])
    transform.Scale(scale)
    return transform

def create_actor(source, color=(0.5, 0.5, 0.5), translate=(0.0, 0.0, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0)):
    actor_transform = transform(translate, rotate, scale)
    mapper = vtkPolyDataMapper()
    mapper.SetInputConnection(source.GetOutputPort())
    actor = vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(color)
    actor.SetUserTransform(actor_transform)
    return actor

def main(argv):
    #####################################################################################################################
    ####################################################### Joint #######################################################
    #####################################################################################################################
    ## Spine ##
    # Pelvis Joint
    pelvis = vtkSphereSource()
    pelvis.SetRadius(0.25)
    pelvActor = create_actor(pelvis, color=(1.0, 0.0, 0.0), translate=(0.0, 0.0, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    # Spine1 Joint
    spine1 = vtkSphereSource()
    spine1.SetRadius(0.25)
    spine1Actor = create_actor(spine1, translate=(0.0, 0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    # Spine2 Joint
    spine2 = vtkSphereSource()
    spine2.SetRadius(0.25)
    spine2Actor = create_actor(spine2, translate=(0.0, 1.0, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    # Spine3 Joint
    spine3 = vtkSphereSource()
    spine3.SetRadius(0.25)
    spine3Actor = create_actor(spine3, translate=(0.0, 1.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    # Neck Joint
    neck = vtkSphereSource()
    neck.SetRadius(0.25)
    neckActor = create_actor(neck, translate=(0.0, 2.75, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    ## Lower Body ##
    # Hip Joint
    leftHip = vtkSphereSource()
    leftHip.SetRadius(0.25)
    leftHipActor = create_actor(leftHip, color=(0.0, 0.75, 0.25), translate=(-0.5, -0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    rightHip = vtkSphereSource()
    rightHip.SetRadius(0.25)
    rightHipActor = create_actor(rightHip, color=(0.0, 0.75, 0.25), translate=(0.5, -0.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    # Knee Joint
    leftKnee = vtkSphereSource()
    leftKnee.SetRadius(0.25)
    leftKneeActor = create_actor(leftKnee, color=(0.0, 0.75, 0.25), translate=(-0.5, -1.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    rightKnee = vtkSphereSource()
    rightKnee.SetRadius(0.25)
    rightKneeActor = create_actor(rightKnee, color=(0.0, 0.75, 0.25), translate=(0.5, -1.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    # Ankle Joint
    leftAnkle = vtkSphereSource()
    leftAnkle.SetRadius(0.25)
    leftAnkleActor = create_actor(leftAnkle, color=(0.0, 0.75, 0.25), translate=(-0.5, -2.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    rightAnkle = vtkSphereSource()
    rightAnkle.SetRadius(0.25)
    rightAnkleActor = create_actor(rightAnkle, color=(0.0, 0.75, 0.25), translate=(0.5, -2.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    ## Upper Body ##
    # Collar Joint
    leftCollar = vtkSphereSource()
    leftCollar.SetRadius(0.25)
    leftCollarActor = create_actor(leftCollar, translate=(-0.5, 2.0, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    rightCollar = vtkSphereSource()
    rightCollar.SetRadius(0.25)
    rightCollarActor = create_actor(rightCollar, translate=(0.5, 2.0, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    # Shoulder Joint
    leftShoulder = vtkSphereSource()
    leftShoulder.SetRadius(0.25)
    leftShoulderActor = create_actor(leftShoulder, color=(0.0, 0.25, 0.75), translate=(-1.0, 2.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    rightShoulder = vtkSphereSource()
    rightShoulder.SetRadius(0.25)
    rightShoulderActor = create_actor(rightShoulder, color=(0.0, 0.25, 0.75), translate=(1.0, 2.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    # Elbow Joint
    leftElbow = vtkSphereSource()
    leftElbow.SetRadius(0.25)
    leftElbowActor = create_actor(leftElbow, color=(0.0, 0.25, 0.75), translate=(-1.75, 2.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    rightElbow = vtkSphereSource()
    rightElbow.SetRadius(0.25)
    rightElbowActor = create_actor(rightElbow, color=(0.0, 0.25, 0.75), translate=(1.75, 2.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    # Wrist Joint
    leftWrist = vtkSphereSource()
    leftWrist.SetRadius(0.25)
    leftWristActor = create_actor(leftWrist, color=(0.0, 0.25, 0.75), translate=(-2.5, 2.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    rightWrist = vtkSphereSource()
    rightWrist.SetRadius(0.25)
    rightWristActor = create_actor(rightWrist, color=(0.0, 0.25, 0.75), translate=(2.5, 2.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    #####################################################################################################################
    ##################################################### Body Part #####################################################
    #####################################################################################################################
    ## Spine ##
    pelvis2spine1 = vtkCylinderSource()
    pelvis2spine1.SetRadius(0.1)
    pelvis2spine1.SetHeight(0.5)
    pelvis2spine1.SetResolution(100)
    pelvis2spine1Actor = create_actor(pelvis2spine1, translate=(0.0, 0.25, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    spine12spine2 = vtkCylinderSource()
    spine12spine2.SetRadius(0.1)
    spine12spine2.SetHeight(0.5)
    spine12spine2.SetResolution(100)
    spine12spine2Actor = create_actor(spine12spine2, translate=(0.0, 0.75, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    spine22spine3 = vtkCylinderSource()
    spine22spine3.SetRadius(0.1)
    spine22spine3.SetHeight(0.5)
    spine22spine3.SetResolution(100)
    spine22spine3Actor = create_actor(spine22spine3, translate=(0.0, 1.25, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    neck2head = vtkCylinderSource()
    neck2head.SetRadius(0.1)
    neck2head.SetHeight(0.5)
    neck2head.SetResolution(100)
    neck2headActor = create_actor(neck2head, translate=(0.0, 3.0, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    Head = vtkSphereSource()
    Head.SetRadius(0.5)
    HeadActor = create_actor(Head, color=(1.0, 1.0, 1.0), translate=(0.0, 3.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    
    ## Lower Body ##
    # Thigh
    leftthigh = vtkCylinderSource()
    leftthigh.SetRadius(0.1)
    leftthigh.SetHeight(0.5)
    leftthigh.SetResolution(100)
    leftthighActor = create_actor(leftthigh, translate=(-0.25, -0.25, 0.0), rotate=(0.0, 0.0, -45.0), scale=(1.0, 1.0, 1.0))

    rightthigh = vtkCylinderSource()
    rightthigh.SetRadius(0.1)
    rightthigh.SetHeight(0.5)
    rightthigh.SetResolution(100)
    rightthighActor = create_actor(rightthigh, translate=(0.25, -0.25, 0.0), rotate=(0.0, 0.0, 45.0), scale=(1.0, 1.0, 1.0))

    # Upper Leg
    leftUpperLeg = vtkCylinderSource()
    leftUpperLeg.SetRadius(0.1)
    leftUpperLeg.SetHeight(1.0)
    leftUpperLeg.SetResolution(100)
    leftUpperLegActor = create_actor(leftUpperLeg, color=(0.0, 0.75, 0.25), translate=(-0.5, -1.0, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    rightUpperLeg = vtkCylinderSource()
    rightUpperLeg.SetRadius(0.1)
    rightUpperLeg.SetHeight(1.0)
    rightUpperLeg.SetResolution(100)
    rightUpperLegActor = create_actor(rightUpperLeg, color=(0.0, 0.75, 0.25), translate=(0.5, -1.0, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    # Lower Leg
    leftLowerLeg = vtkCylinderSource()
    leftLowerLeg.SetRadius(0.1)
    leftLowerLeg.SetHeight(1.0)
    leftLowerLeg.SetResolution(100)
    leftLowerLegActor = create_actor(leftLowerLeg, color=(0.0, 0.75, 0.25), translate=(-0.5, -2.0, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    rightLowerLeg = vtkCylinderSource()
    rightLowerLeg.SetRadius(0.1)
    rightLowerLeg.SetHeight(1.0)
    rightLowerLeg.SetResolution(100)
    rightLowerLegActor = create_actor(rightLowerLeg, color=(0.0, 0.75, 0.25), translate=(0.5, -2.0, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    # Foot
    leftFoot = vtkCubeSource()
    leftFoot.SetXLength(0.35)
    leftFoot.SetYLength(0.1)
    leftFoot.SetZLength(0.5)
    leftFootActor = create_actor(leftFoot, color=(1.0, 1.0, 0.0), translate=(-0.5, -2.65, 0.25), rotate=(180.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    rightFoot = vtkCubeSource()
    rightFoot.SetXLength(0.35)
    rightFoot.SetYLength(0.1)
    rightFoot.SetZLength(0.5)
    rightFootActor = create_actor(rightFoot, color=(1.0, 1.0, 0.0), translate=(0.5, -2.65, 0.25), rotate=(180.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    ## Upper Body ##
    # Thorax
    leftThorax = vtkCylinderSource()
    leftThorax.SetRadius(0.1)
    leftThorax.SetHeight(0.5)
    leftThorax.SetResolution(100)
    leftThoraxActor = create_actor(leftThorax, translate=(-0.2, 1.7, 0.0), rotate=(0.0, 0.0, 45.0), scale=(1.0, 1.0, 1.0))

    rightThorax = vtkCylinderSource()
    rightThorax.SetRadius(0.1)
    rightThorax.SetHeight(0.5)
    rightThorax.SetResolution(100)
    rightThoraxActor = create_actor(rightThorax, translate=(0.2, 1.7, 0.0), rotate=(0.0, 0.0, -45.0), scale=(1.0, 1.0, 1.0))

    # Lower Clavicle
    leftLowerClavicle = vtkCylinderSource()
    leftLowerClavicle.SetRadius(0.1)
    leftLowerClavicle.SetHeight(0.5)
    leftLowerClavicle.SetResolution(100)
    leftLowerClavicleActor = create_actor(leftLowerClavicle, translate=(-0.75, 2.25, 0.0), rotate=(0.0, 0.0, 45.0), scale=(1.0, 1.0, 1.0))

    rightLowerClavicle = vtkCylinderSource()
    rightLowerClavicle.SetRadius(0.1)
    rightLowerClavicle.SetHeight(0.5)
    rightLowerClavicle.SetResolution(100)
    rightLowerClavicleActor = create_actor(rightLowerClavicle, translate=(0.75, 2.25, 0.0), rotate=(0.0, 0.0, -45.0), scale=(1.0, 1.0, 1.0))

    # Upper Clavicle
    leftUpperClavicle = vtkCylinderSource()
    leftUpperClavicle.SetRadius(0.1)
    leftUpperClavicle.SetHeight(0.75)
    leftUpperClavicle.SetResolution(100)
    leftUpperClavicleActor = create_actor(leftUpperClavicle, translate=(-0.5, 2.6, 0.0), rotate=(0.0, 0.0, -75.0), scale=(1.0, 1.0, 1.0))

    rightUpperClavicle = vtkCylinderSource()
    rightUpperClavicle.SetRadius(0.1)
    rightUpperClavicle.SetHeight(0.75)
    rightUpperClavicle.SetResolution(100)
    rightUpperClavicleActor = create_actor(rightUpperClavicle, translate=(0.5, 2.6, 0.0), rotate=(0.0, 0.0, 75.0), scale=(1.0, 1.0, 1.0))

    # Upper Arm
    leftUpperArm = vtkCylinderSource()
    leftUpperArm.SetRadius(0.1)
    leftUpperArm.SetHeight(0.75)
    leftUpperArm.SetResolution(100)
    leftUpperArmActor = create_actor(leftUpperArm, color=(0.0, 0.25, 0.75), translate=(-1.5, 2.5, 0.0), rotate=(0.0, 0.0, 90.0), scale=(1.0, 1.0, 1.0))

    rightUpperArm = vtkCylinderSource()
    rightUpperArm.SetRadius(0.1)
    rightUpperArm.SetHeight(0.75)
    rightUpperArm.SetResolution(100)
    rightUpperArmActor = create_actor(rightUpperArm, color=(0.0, 0.25, 0.75), translate=(1.5, 2.5, 0.0), rotate=(0.0, 0.0, -90.0), scale=(1.0, 1.0, 1.0))

    # Lower Arm
    leftLowerArm = vtkCylinderSource()
    leftLowerArm.SetRadius(0.1)
    leftLowerArm.SetHeight(0.75)
    leftLowerArm.SetResolution(100)
    leftLowerArmActor = create_actor(leftLowerArm, color=(0.0, 0.25, 0.75), translate=(-2.0, 2.5, 0.0), rotate=(0.0, 0.0, 90.0), scale=(1.0, 1.0, 1.0))

    rightLowerArm = vtkCylinderSource()
    rightLowerArm.SetRadius(0.1)
    rightLowerArm.SetHeight(0.75)
    rightLowerArm.SetResolution(100)
    rightLowerArmActor = create_actor(rightLowerArm, color=(0.0, 0.25, 0.75), translate=(2.0, 2.5, 0.0), rotate=(0.0, 0.0, -90.0), scale=(1.0, 1.0, 1.0))

    # Hand
    leftHand = vtkCubeSource()
    leftHand.SetXLength(0.35)
    leftHand.SetYLength(0.35)
    leftHand.SetZLength(0.1)
    leftHandActor = create_actor(leftHand, color=(1.0, 1.0, 0.0), translate=(-2.75, 2.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    rightHand = vtkCubeSource()
    rightHand.SetXLength(0.35)
    rightHand.SetYLength(0.35)
    rightHand.SetZLength(0.1)
    rightHandActor = create_actor(rightHand, color=(1.0, 1.0, 0.0), translate=(2.75, 2.5, 0.0), rotate=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))

    #####################################################################################################################
    ###################################################### Render #######################################################
    #####################################################################################################################
    colors = vtkNamedColors()
    
    ## Renderer1 ##
    renderer1 = vtkRenderer()
    renderer1.SetBackground(colors.GetColor3d('SlateGray'))

    # Add Actor
    # Joint
    renderer1.AddActor(pelvActor)
    renderer1.AddActor(spine1Actor)
    renderer1.AddActor(spine2Actor)
    renderer1.AddActor(spine3Actor)
    renderer1.AddActor(neckActor)
    renderer1.AddActor(leftHipActor)
    renderer1.AddActor(rightHipActor)
    renderer1.AddActor(leftKneeActor)
    renderer1.AddActor(rightKneeActor)
    renderer1.AddActor(leftAnkleActor)
    renderer1.AddActor(rightAnkleActor)
    renderer1.AddActor(leftCollarActor)
    renderer1.AddActor(rightCollarActor)
    renderer1.AddActor(leftShoulderActor)
    renderer1.AddActor(rightShoulderActor)
    renderer1.AddActor(leftElbowActor)
    renderer1.AddActor(rightElbowActor)
    renderer1.AddActor(leftWristActor)
    renderer1.AddActor(rightWristActor)

    # Body Part
    renderer1.AddActor(pelvis2spine1Actor)
    renderer1.AddActor(spine12spine2Actor)
    renderer1.AddActor(spine22spine3Actor)
    renderer1.AddActor(neck2headActor)
    renderer1.AddActor(HeadActor)
    renderer1.AddActor(leftthighActor)
    renderer1.AddActor(rightthighActor)
    renderer1.AddActor(leftUpperLegActor)
    renderer1.AddActor(rightUpperLegActor)
    renderer1.AddActor(leftLowerLegActor)
    renderer1.AddActor(rightLowerLegActor)
    renderer1.AddActor(leftFootActor)
    renderer1.AddActor(rightFootActor)
    renderer1.AddActor(leftThoraxActor)
    renderer1.AddActor(rightThoraxActor)
    renderer1.AddActor(leftLowerClavicleActor)
    renderer1.AddActor(rightLowerClavicleActor)
    renderer1.AddActor(leftUpperClavicleActor)
    renderer1.AddActor(rightUpperClavicleActor)
    renderer1.AddActor(leftUpperArmActor)
    renderer1.AddActor(rightUpperArmActor)
    renderer1.AddActor(leftLowerArmActor)
    renderer1.AddActor(rightLowerArmActor)
    renderer1.AddActor(leftHandActor)
    renderer1.AddActor(rightHandActor)

    ## Renderer2 ##
    renderer2 = vtkRenderer()
    quadric = vtkQuadric()
    quadric.SetCoefficients(1, 2, 3, 0, 1, 0, 0, 0, 0, 0)

    sample = vtkSampleFunction()
    sample.SetSampleDimensions(25, 25, 25)
    sample.SetImplicitFunction(quadric)

    isoActor = vtkActor()
    CreateIsosurface(sample, isoActor)
    outlineIsoActor = vtkActor()
    CreateOutline(sample, outlineIsoActor)

    planesActor = vtkActor()
    CreatePlanes(sample, planesActor, 5)
    outlinePlanesActor = vtkActor()
    CreateOutline(sample, outlinePlanesActor)
    planesActor.AddPosition(isoActor.GetBounds()[0] * 2.0, 0, 0)
    outlinePlanesActor.AddPosition(isoActor.GetBounds()[0] * 2.0, 0, 0)

    contourActor = vtkActor()
    CreateContours(sample, contourActor, 3, 15)
    outlineContourActor = vtkActor()
    CreateOutline(sample, outlineContourActor)
    contourActor.AddPosition(isoActor.GetBounds()[0] * 4.0, 0, 0)
    outlineContourActor.AddPosition(isoActor.GetBounds()[0] * 4.0, 0, 0)

    renderer2.AddActor(planesActor)
    renderer2.AddActor(outlinePlanesActor)
    renderer2.AddActor(contourActor)
    renderer2.AddActor(outlineContourActor)
    renderer2.AddActor(isoActor)
    renderer2.AddActor(outlineIsoActor)
    renderer2.TwoSidedLightingOn()
    renderer2.SetBackground(colors.GetColor3d("SlateGray"))
    renderer2.GetActiveCamera().SetPosition(0, -1, 0)
    renderer2.GetActiveCamera().SetFocalPoint(0, 0, 0)
    renderer2.GetActiveCamera().SetViewUp(0, 0, -1)
    renderer2.ResetCamera()
    renderer2.GetActiveCamera().Elevation(20)
    renderer2.GetActiveCamera().Azimuth(10)
    renderer2.GetActiveCamera().Dolly(1.2)
    renderer2.ResetCameraClippingRange()

    # Render Window
    renderer1.SetViewport(0.0, 0.0, 0.5, 1.0)
    renderer2.SetViewport(0.5, 0.0, 1.0, 1.0)
    renderWindow = vtkRenderWindow()
    renderWindow.AddRenderer(renderer1)
    renderWindow.AddRenderer(renderer2)
    renderWindow.SetSize(500, 700)
    renderWindow.SetWindowName('Full_Human_Model_T_Pose')
    interactor = vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)
    style = vtkInteractorStyleTrackballCamera()
    interactor.SetInteractorStyle(style)
    renderWindow.Render()
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