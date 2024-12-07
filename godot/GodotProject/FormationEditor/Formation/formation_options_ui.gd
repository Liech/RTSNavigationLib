extends Control

@onready var name_ui : LineEdit = $S/M/Stats/Stats/Name
@onready var placement_behavior_ui : OptionButton = $S/M/Stats/Stats/PlacementBehavior
@onready var category_ui : OptionButton = $S/M/Stats/Stats/Category
@onready var rotate_with_interface_ui : CheckBox = $S/M/Stats/Stats/RotateWithInterface
@onready var rotation_ui : Slider = $S/M/Stats/Stats/Rotation
@onready var interface_width_ui : CheckBox = $S/M/Stats/Stats/InterfaceWidth
@onready var weight_ui : Slider = $S/M/Stats/Stats/Weight
@onready var own_interface_ui : SpinBox =$S/M/Stats/Stats/OwnInterface
@onready var parent_interface_ui : SpinBox = $S/M/Stats/Stats/ParentInterface

func _ready() -> void:
	FormationEditor.current_formation_changed.connect(current_formation_changed)
	current_formation_changed()

func current_formation_changed()->void:
	if (FormationEditor.current_formation == null):
		visible = false
		return
	visible = true
	var current := FormationEditor.current_formation
	name_ui.text = current.name
	placement_behavior_ui.select(int(current.placement_behavior))
	category_ui.text = current.category
	rotate_with_interface_ui.button_pressed = current.rotate_with_interface
	rotation_ui.value = current.rotation
	interface_width_ui.button_pressed = current.overwrite_width_with_interface_width
	weight_ui.value = current.weight
	own_interface_ui.value = current.own_InterfacePoint
	parent_interface_ui.value = current.parent_interface_point
	
