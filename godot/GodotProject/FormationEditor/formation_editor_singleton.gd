class_name FormationEditorSingleton extends Node

signal categories_changed;
signal unit_types_changed;
signal formations_changed;

var categories : Array[String] 
var unit_types : Array[UnitType]
var formations : Array[Formation]

var unit_amount : Dictionary = {}
