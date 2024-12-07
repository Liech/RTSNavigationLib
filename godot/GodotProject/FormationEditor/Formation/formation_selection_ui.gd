extends MarginContainer


@onready var list : ItemList = $M/V/M/FormationList

func _ready() -> void:
	FormationEditor.formations_changed.connect(formation_changed)
	formation_changed()
	

func formation_changed() -> void:
	list.clear()
	for x in FormationEditor.formations:
		list.add_item(x.name)
	
func _on_select_pressed() -> void:
	if (!list.is_anything_selected()):
		return
	var index : int = list.get_selected_items()[0]
	FormationEditor.current_formation = FormationEditor.formations[index]
	FormationEditor.current_formation_changed.emit()

func _on_delete_pressed() -> void:
	if (!list.is_anything_selected()):
		return
	var index : int = list.get_selected_items()[0]
	FormationEditor.formations.remove_at(index)
	FormationEditor.formations_changed.emit()
	
func _on_add_pressed() -> void:
	var new_formation : Formation = Formation.new()
	new_formation.randomize()

	FormationEditor.formations.append(new_formation)
	FormationEditor.formations_changed.emit()
	
