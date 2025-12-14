extends Node

func _ready() -> void:
	test_plugin_functionality()

func test_plugin_functionality()->void:
	var test:Splashscreen = Splashscreen.new()
	
	$Sprite2D.texture = test.Screenshot()
	
	
	
	
