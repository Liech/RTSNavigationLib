extends MarginContainer

@onready var Title : Label = $M/V/Title
@onready var Amount : Label = $M/V/HBoxContainer/Numbers
@onready var slide : HSlider = $M/V/HBoxContainer/AmountSlider

var index : int = 0

func _ready() -> void:
	FormationEditor.unit_types_changed.connect(unit_types_changed)
	unit_types_changed()
	
func unit_types_changed() -> void:
	if (index >= FormationEditor.unit_types.size()):
		return
	Title.text = FormationEditor.unit_types[index].name
