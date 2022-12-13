**Restyle** is a plugin for **Unreal Engine** v5.0, v5.1 that brings a brand new new look for graph editors.

Restyle replaces graph editor's widgets with customizable versions while also leaving overall engine look unchanged.

## Table of Contents: <a name="toc"></a>
- [Gallery](#gallery)
- [Installation](#installation)
- [Motivation](#motivation)
- [Features](#features) 
- [Difficulties](#difficulties)
- [FAQ](#faq)

## [=](#toc) Gallery <a name="gallery"></a>
<img src="https://images2.imgbox.com/42/c2/ykKTc81Y_o.png" alt="image host"/>
<a href="https://imgbox.com/g/pXWcf0Yyfg">Image Gallery</a> - You can find here how plugin does look

## [=](#toc) Installation <a name="installation"></a>
Goto your unreal engine's project directory (should contain .uproject file in there) 

Then run **one** of the following commands:
- For UE v5.0
```
git clone --single-branch --branch v5_0 https://github.com/agitoreiken/ue-restyle ./Plugins/Restyle
```
- For UE v5.1
```
git clone --single-branch --branch v5_1 ttps://github.com/agitoreiken/ue-restyle ./Plugins/Restyle
``` 

## [=](#toc) Motivation <a name="motivation"></a>
I did really want to see new design for blueprints in ue-5, but that didn't happen. 

So i've searched through the marketplace, found some projects: 

- The first one was free, but had visual issues.
- The second one did seem better, but was paid. I couldn't afford it.

At the end of the day i decided to take the reponsibility and bring the thing i wanted to see
<details>
  <summary>Spoiler</summary>
  It took a 6 unprofittable months lmao
</details> 


## [=](#toc) Features <a name="features"></a>
Plugin is made of 3 factory providers which represents factories inside of FEdGraphUtilities, which are used by engine to spawn Nodes, Pins, Connections.

### General
- New SVG icons
- New widgets
- Almost everything is configurable with styles (Colors, Spacings, Sizes, Brushes, Buttons...)

### Nodes
- 3 States (Normal, Selected, Invalid)
- New title style 
- Ability to disable "Target Is"

### Variable Nodes
- Ability to hide "GET" title [Optional]

### Compact Nodes
- New title style with ability to apply it if title length exceeds <n>
- Background icons for Function and Macro

### Reroute
- Shows "drag" boundaries on hover

### Comments
- New resizing method (which prevents cursor slide off comment)
- Opacity level is set by default (For normal, selected states)

### Comment Bubbles (Its not bubble)
- Buttons shows only if widget is hovered

### Node Reports (error/warning etc.) and State (development/disabled)
- Title is configurable

### Pin Connections
- New style for wires, featuring 45° & 90° alignment
- Prioritizing in context of input/output pins for line length and/or position 
(Works for left->right & right->left transitions, also exec<->reroute have their own prioritization)

- Squared, rounded corners
- Radius (up to 0.5 of length, visually shortens the path)
- Optimized for backward routing (has snap points)
- Custom bubble settings
- Nested wire for animation's attributes instead of spaghetti
  
### Pins
- Custom colors [Optional]
- Custom pin-constructors (Vector4 is only available atm)
  <details>
  <summary>Thoughts</summary>
    Maybe having pin constructors for structures with short constructors isn't that bad
  </details> 
- Vector that is Rotator may use new labels (RPY) [Optional]
- Custom text for "Add Pin" [Optional]
### Zoom [Optional]
- Ability to set or even generate zoom behavior

## Recommendations (likely to change)
Windows OC, because MinHook library (i get used to) doesn't support other systems. It's used to redesign CreateWidget node. Thats probably all atm.
You can run it anyway on any other system, just this widget will be with unreal style.


## [=](#toc) Difficulties <a name="difficulties"></a>

### Technical Side
To apply on "design" behavior of SGraphNode/SGraphPin classes, the new ones needed to be created.

Because some of them are not exported for external use, it becomes impossible to mantain the inheritance;

In simple words. All SGraphNodes are still SGraphNodes, but all SGraphNodeK2 are now S**Default**GraphNodeK2, 
and all logic inside of SGraphNodeK2 was copy-pasted to Restyle's classes.

**For each logical update on widgets made in newer versions of Unreal, the plugin must be updated in order to match them**

### User Experience
Do not try to change settings while working with graphs. Close them, make a change and only then open. 
Otherwise, editor will crash (due to style changes)

Having opened "Editor Settings" window with restyle loaded may cause editor to slow down. (For some reason slate processess non-visible options) 
 

## [=](#toc) FAQ <a name="faq"></a>
### **Could it break my data?** 
If you are not trying to force old plugin version works on new unreal version then **no**. 
  In the worst case of the plugin malfunction you will not see some widget element or it's style is still an old one :)
  
But if you really curious about your data safety, use external backup system (not git), because this engine is pretty volatile thing itself. 
  
### **I have my own factories defined, will it work?**
Plugin registers factories at Index 0 and they check if there is any other factory wants to spawn that UClass. 
So yes it will work, but styles will mismatch (ways of fixing this part are not discussed nor done yet)
