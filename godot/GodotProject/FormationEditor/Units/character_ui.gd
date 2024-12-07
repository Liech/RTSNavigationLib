class_name character_ui extends Node

@onready var category_ui : OptionButton = $MarginContainer/Content/Stats/OptionButton
@onready var size_ui : SpinBox = $MarginContainer/Content/Stats/SizeEdit
@onready var color_ui : ColorPickerButton = $MarginContainer/Content/Stats/ColorPickerButton
@onready var name_ui : LineEdit = $MarginContainer/Content/Stats/NameEdit
@onready var emoji_ui : LineEdit = $MarginContainer/Content/Stats/Emoji

@export var index : int = 0

func _ready() -> void:
	FormationEditor.categories_changed.connect(categories_changed)
	FormationEditor.unit_types_changed.connect(unit_types_changed)
	categories_changed()
	unit_types_changed()
	
func categories_changed() -> void:
	category_ui.clear()
	for x in FormationEditor.categories:
		category_ui.add_item(x)

func unit_types_changed() -> void:
	if (index >= FormationEditor.unit_types.size()):
		queue_free()
		return
	var type := FormationEditor.unit_types[index]
	color_ui.color = type.color
	size_ui.value = type.size
	name_ui.text = type.name
	emoji_ui.text = type.emoji
	category_ui.text = type.category

func _on_delete_pressed() -> void:
	FormationEditor.unit_types.remove_at(index)
	FormationEditor.unit_types_changed.emit()

func _on_duplicate_pressed() -> void:
	if (FormationEditor.categories.size() == 0):
		return
	var newType : UnitType = UnitType.new()
	newType.name = ["Sword","Dagger","Fist","Arrow","Bow","Lance","Rock","Shield"].pick_random()
	newType.name += [" Thrower"," Master"," Cleric","man"," Elite"," Basher", " Wielder", " Savant"].pick_random()
	newType.emoji = ["🗡️","🏹","🧙","😀","😅","😇","🤑","😬","🥶","🥵","🤠","😱","🤡","☠","👹","😾","💗"].pick_random()
	newType.color = Color(randf(),randf(),randf())
	newType.size = 1
	newType.category = FormationEditor.categories.pick_random()
	FormationEditor.unit_types.push_back(newType)
	FormationEditor.unit_types_changed.emit()
