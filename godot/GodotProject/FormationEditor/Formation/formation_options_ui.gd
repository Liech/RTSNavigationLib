extends Control

@onready var name_ui : LineEdit = $S/M/Stats/Stats/Name
@onready var placement_behavior_ui : OptionButton = $S/M/Stats/Stats/PlacementBehavior
@onready var category_ui : Button = $S/M/Stats/Stats/Category
@onready var category_menu_ui : PopupMenu = $CategoryMenu
@onready var rotate_with_interface_ui : CheckBox = $S/M/Stats/Stats/RotateWithInterface
@onready var rotation_ui : Slider = $S/M/Stats/Stats/Rotation
@onready var interface_width_ui : CheckBox = $S/M/Stats/Stats/InterfaceWidth
@onready var weight_ui : Slider = $S/M/Stats/Stats/Weight
@onready var own_interface_ui : SpinBox =$S/M/Stats/Stats/OwnInterface
@onready var parent_interface_ui : SpinBox = $S/M/Stats/Stats/ParentInterface
@onready var arc_label_ui : Label = $S/M/Stats/Stats/ArcLabel
@onready var arc_ui : Slider = $S/M/Stats/Stats/Arc
@onready var shape_ui : OptionButton = $S/M/Stats/Stats/Shape
@onready var hollow_ui : Slider = $S/M/Stats/Stats/Hollow
@onready var scaling_behavior_ui : OptionButton = $S/M/Stats/Stats/ScalingBehavior
@onready var size_x_ui : SpinBox= $S/M/Stats/Stats/Size/SizeX
@onready var size_y_ui : SpinBox= $S/M/Stats/Stats/Size/SizeY


func _ready() -> void:
	FormationEditor.current_formation_changed.connect(current_formation_changed)
	FormationEditor.categories_changed.connect(categories_changed)
	categories_changed()
	current_formation_changed()	

func categories_changed()->void:
	category_menu_ui.clear()
	for x in FormationEditor.categories:
		category_menu_ui.add_item(x)
		category_menu_ui.set_item_as_checkable(category_menu_ui.item_count-1,true)

func current_formation_changed()->void:
	if (FormationEditor.current_formation == null):
		visible = false
		return
	visible = true
	var current := FormationEditor.current_formation
	name_ui.text = current.name
	placement_behavior_ui.select(int(current.placement_behavior))
	rotate_with_interface_ui.button_pressed = current.rotate_with_interface
	rotation_ui.value = current.rotation
	interface_width_ui.button_pressed = current.overwrite_width_with_interface_width
	weight_ui.value = current.weight
	own_interface_ui.value = current.own_InterfacePoint
	parent_interface_ui.value = current.parent_interface_point
	shape_ui.selected = current.shape as int
	arc_ui.value = current.arc
	hollow_ui.value = current.hollow
	scaling_behavior_ui.selected = current.scaling_behavior
	size_x_ui.value = current.size.x
	size_y_ui.value = current.size.y
	
	for x in range(category_menu_ui.item_count):
		category_menu_ui.set_item_checked(x,false)
	category_ui.text = "";
	for x in FormationEditor.current_formation.category:
		category_ui.text+= x + "; "
	for x in current.category:
		category_menu_ui.set_item_checked(FormationEditor.categories.find(x),true)
	update_bounds()
	
func update_bounds()->void:
	var current := FormationEditor.current_formation
	arc_ui.visible = current.shape == Formation.Shape.Circle
	arc_label_ui.visible = current.shape == Formation.Shape.Circle
	
func _on_name_text_submitted(_new_text: String) -> void:
	FormationEditor.current_formation.name = name_ui.text
	FormationEditor.formations_changed.emit()
func _on_placement_behavior_item_selected(index: int) -> void:
	FormationEditor.current_formation.placement_behavior = index as RTSFormation.PlacementBehavior
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
	@warning_ignore("narrowing_conversion")
	FormationEditor.current_formation.own_InterfacePoint = value
	FormationEditor.formation_value_changed.emit()
func _on_parent_interface_value_changed(value: float) -> void:
	@warning_ignore("narrowing_conversion")
	FormationEditor.current_formation.parent_interface_point = value
	FormationEditor.formation_value_changed.emit()
func _on_shape_item_selected(index: int) -> void:
	@warning_ignore("int_as_enum_without_cast")
	FormationEditor.current_formation.shape = index
	FormationEditor.formation_value_changed.emit()
	update_bounds()
func _on_arc_drag_ended(value_changed: bool) -> void:
	if (!value_changed):
		return
	FormationEditor.current_formation.arc = arc_ui.value
	FormationEditor.formation_value_changed.emit()
func _on_category_pressed() -> void:
	@warning_ignore("narrowing_conversion")
	category_menu_ui.popup(Rect2i(get_global_mouse_position().x, get_global_mouse_position().y, 100, 30))

func _on_category_menu_index_pressed(index: int) -> void:
	category_menu_ui.set_item_checked(index,!category_menu_ui.is_item_checked(index))
	if (category_menu_ui.is_item_checked(index)):
		FormationEditor.current_formation.category.push_back(FormationEditor.categories[index])
	else:
		FormationEditor.current_formation.category.erase(FormationEditor.categories[index])
	
	category_ui.text = "";
	for x in FormationEditor.current_formation.category:
		category_ui.text+= x + " "

func _on_category_menu_popup_hide() -> void:
	FormationEditor.formation_value_changed.emit()

func _on_scaling_behavior_item_selected(index: int) -> void:
	@warning_ignore("int_as_enum_without_cast")
	FormationEditor.current_formation.scaling_behavior = index
	FormationEditor.formation_value_changed.emit()

func _on_hollow_drag_ended(_value_changed: bool) -> void:
	FormationEditor.current_formation.hollow = hollow_ui.value
	FormationEditor.formation_value_changed.emit()

func _on_size_y_value_changed(value: float) -> void:
	FormationEditor.current_formation.size.y = size_y_ui.value
	FormationEditor.formation_value_changed.emit()
	
func _on_size_x_value_changed(value: float) -> void:
	FormationEditor.current_formation.size.x = size_x_ui.value
	FormationEditor.formation_value_changed.emit()
