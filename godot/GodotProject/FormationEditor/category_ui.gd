extends MarginContainer

@onready var list : ItemList = $Menu/List/CategoryList
@onready var categoryName : LineEdit = $Menu/NewCategory

func _ready() -> void:
	FormationEditor.categories_changed.connect(categories_changed)
	categories_changed()

func categories_changed() -> void:
	print(FormationEditor.categories)
	list.clear();
	list.deselect_all()		
	for x in FormationEditor.categories:
		list.add_item(x)

func _on_delete_pressed() -> void:
	if (list.is_anything_selected()):
		var sel : int =list.get_selected_items()[0]
		FormationEditor.categories.remove_at(sel)
		FormationEditor.categories_changed.emit()

func _on_add_pressed() -> void:
	if (categoryName.text.length() == 0):
		return
	for x in FormationEditor.categories:
		if (x == categoryName.text):
			return;
	FormationEditor.categories.append(categoryName.text)
	categoryName.text = ""
	FormationEditor.categories_changed.emit()
