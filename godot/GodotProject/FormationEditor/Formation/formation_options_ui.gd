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
@onready var arc_label_ui : Label = $S/M/Stats/Stats/ArcLabel
@onready var arc_ui : Slider = $S/M/Stats/Stats/Arc
@onready var shape_ui : OptionButton = $S/M/Stats/Stats/Shape


func _ready() -> void:
	FormationEditor.current_formation_changed.connect(current_formation_changed)
	FormationEditor.categories_changed.connect(categories_changed)
	categories_changed()
	current_formation_changed()	

func categories_changed()->void:
	category_ui.clear()
	for x in FormationEditor.categories:
		category_ui.add_item(x)

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
	shape_ui.selected = current.shape as int
	arc_ui.value = current.arc
	update_bounds()
	
func update_bounds()->void:
	var current := FormationEditor.current_formation
	arc_ui.visible = current.shape == Formation.Shape.Circle
	arc_label_ui.visible = current.shape == Formation.Shape.Circle
	
	
func _on_name_text_submitted(new_text: String) -> void:
	FormationEditor.current_formation.name = name_ui.text
	FormationEditor.formations_changed.emit()
func _on_placement_behavior_item_selected(index: int) -> void:
	FormationEditor.current_formation.placement_behavior = index as RTSFormation.PlacementBehavior
	FormationEditor.formation_value_changed.emit()
func _on_category_item_selected(index: int) -> void:
	FormationEditor.current_formation.category = FormationEditor.categories[index]
	FormationEditor.formation_value_changed.emit()
func _on_rotate_with_interface_toggled(toggled_on: bool) -> void:
	FormationEditor.current_formation.rotate_with_interface = toggled_on
	FormationEditor.formation_value_changed.emit()
func _on_rotation_drag_ended(value_changed: bool) -> void:
	if (!value_changed):
		return
	FormationEditor.current_formation.rotation = rotation_ui.value
	FormationEditor.formation_value_changed.emit()
func _on_interface_width_toggled(toggled_on: bool) -> void:
	FormationEditor.current_formation.overwrite_width_with_interface_width = toggled_on
	FormationEditor.formation_value_changed.emit()
func _on_weight_drag_ended(value_changed: bool) -> void:
	if (!value_changed):
		return
	FormationEditor.current_formation.weight = weight_ui.value
	FormationEditor.formation_value_changed.emit()
func _on_own_interface_value_changed(value: float) -> void:
	FormationEditor.current_formation.own_InterfacePoint = value
	FormationEditor.formation_value_changed.emit()
func _on_parent_interface_value_changed(value: float) -> void:
	FormationEditor.current_formation.parent_interface_point = value
	FormationEditor.formation_value_changed.emit()
func _on_shape_item_selected(index: int) -> void:
	update_bounds()
	FormationEditor.current_formation.shape = index
	FormationEditor.formation_value_changed.emit()
func _on_arc_drag_ended(value_changed: bool) -> void:
	if (!value_changed):
		return
	FormationEditor.current_formation.arc = arc_ui.value
	FormationEditor.formation_value_changed.emit()
