extends MarginContainer

@onready var Title : Label = $M/V/Title
@onready var Amount : SpinBox = $M/V/HBoxContainer/Numbers
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

func unit_amount_changed() -> void:
	if FormationEditor.unit_amount.has(FormationEditor.unit_types[index].name):
		Amount.value = FormationEditor.unit_amount[FormationEditor.unit_types[index].name]
		slide.value = FormationEditor.unit_amount[FormationEditor.unit_types[index].name]
	else:
		Amount.value = 0
		slide.value = 0

func _on_amount_slider_drag_ended(value_changed: bool) -> void:
	if (!value_changed):
		return
	FormationEditor.unit_amount[FormationEditor.unit_types[index].name] = int(slide.value);
	unit_amount_changed()
	FormationEditor.unit_amount_changed.emit()

func _on_amount_slider_changed() -> void:
	Amount.text = str(slide.value)

func _on_numbers_value_changed(value: float) -> void:
	var change : bool = true
	if (FormationEditor.unit_amount.has(FormationEditor.unit_types[index].name)):
		change = FormationEditor.unit_amount[FormationEditor.unit_types[index].name] != int(Amount.value);
	if (change):
		FormationEditor.unit_amount[FormationEditor.unit_types[index].name] = int(Amount.value);
		FormationEditor.unit_amount_changed.emit()
