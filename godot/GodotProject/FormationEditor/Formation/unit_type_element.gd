extends MarginContainer

@onready var Title : Label = $M/V/Title
@onready var Amount : Label = $M/V/HBoxContainer/Numbers
@onready var slide : HSlider = $M/V/HBoxContainer/AmountSlider

var index : int = 0

func _ready() -> void:
	FormationEditor.unit_types_changed.connect(unit_types_changed)
	FormationEditor.unit_amount_changed.connect(unit_amount_changed)
	unit_types_changed()
	unit_amount_changed()
	
func unit_types_changed() -> void:
	if (index >= FormationEditor.unit_types.size()):
		return
	Title.text =  FormationEditor.unit_types[index].emoji + " " + FormationEditor.unit_types[index].name
	unit_amount_changed()

func _on_amount_slider_value_changed(value: float) -> void:
	FormationEditor.unit_amount[FormationEditor.unit_types[index].name] = int(value);
	unit_amount_changed()

func unit_amount_changed() -> void:
	if FormationEditor.unit_amount.has(FormationEditor.unit_types[index].name):
		Amount.text = str(FormationEditor.unit_amount[FormationEditor.unit_types[index].name])
		slide.value = FormationEditor.unit_amount[FormationEditor.unit_types[index].name]
	else:
		Amount.text = "0"
		slide.value = 0
