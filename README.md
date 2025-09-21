# Material Design for Qt
**Implementation of Material Design style controls based on Qt**
## How to Use?
1. use **add_sub directory**（Recommend）

```cmake
add_subdirectory(path/to/MaterialDesignControls)
target_link_libraries(YourTarget PRIVATE MaterialDesignControls)
```

2. use **find_package**（need installation）

```cmake
find_package(MaterialDesignControls REQUIRED)
target_link_libraries(YourTarget PRIVATE MaterialDesignControls)
```
## List
### widget
- [ ] MPushButton  The mask layer cannot be removed correctly after the animation is completed
- [ ] MSwichButton
- [ ] MCheckBox
- [ ] MLineEdit
- [ ] MLabel
- [ ] MSlider
- [ ] Mcard
- [ ] MProcessBar
- [ ] MRadioButton
### window
- [ ] MWidget
- [ ] MBox
- [ ] MMessage