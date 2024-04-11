# A-copycat-of-Vampire-Survivor

using QT 5.9.8

# 1. Abstract
"Vampire Survivor" is a Roguelike game launched on Steam in 2021, focusing on the concepts of "mowing" and "survival." The game was highly successful upon release, leading a trend of "survivor" games and becoming a pioneer in the genre. Let's also create a similar survivor game!

## 2. Technical Specifications: Phase One
We referred to some existing survivor games to create these technical specifications. This section introduces the requirements for Phase One.

### 2.1 Map
The game's map is logically an m × n rectangle with boundaries. Each 1 × 1 rectangle is a grid, and enemy units randomly spawn from edge grids. Grids can be shared, meaning multiple units can occupy the same grid.
You can add some destructible/indestructible obstacles in the map; neither enemy nor player units can pass through obstacles. Require at least five grids on the map to have obstacles.

### 2.2 Player
In a survivor game, players take on the role of survivors, with the goal of surviving until a specified time and the failure condition being death before reaching the set time.
The player's base attributes for controlling the character include: health, attack power, and movement speed.
Weapon attributes include: damage area, duration, cooldown time.
You can design different characters, each with unique base attributes and holding a distinctive starting weapon. Require at least two characters for players to choose from.
Player controls are straightforward; all weapons are automatically cast. In combat, players only need one input: moving with WASD. "Movement" here has two logical functions:
1. Attack targets by moving to make the weapon's damage area contact enemies.
2. Evade attacks by moving to avoid taking damage.
If Extension 3.1 (item drops) is implemented, movement will have an additional function: picking up items by moving to cover the drop range.

### 2.3 Enemy Units
In the game, the only threat to players comes from a continuous onslaught of monsters generated and attacking players. Enemy units in a survivor game are designed very simply, with the majority of ordinary monsters only dealing continuous damage when they come into contact with players (in the same map grid). A few elite monsters can attack players from a distance (considered equipped with weapons).
- Enemy units:
  - Basic attributes: health, attack power, movement speed.
  - Appearance method: randomly refresh from the screen edges.
  - Movement strategy: continuously move towards the player's direction, or move in a fixed direction and change direction when reaching the boundary.
  - Attack method: melee (damage area is the unit's grid), ranged (customizable damage area).
Require at least one melee unit and one ranged unit, implementing both movement strategies.

## 3. Technical Specifications: Phase Two
We have completed a simple survivor game! That sounds awesome! So, let's add more content to this game! The game should be based on what was achieved in Phase One, with code refactoring only when necessary.

### 3.1 In-Game Enhancement System
The in-game enhancement system is one of the most representative features of a survivor game.
New setting: experience points, levels, enhancements. Players gain experience points by killing monsters, and when experience points meet the level-up conditions, players level up, allowing for in-game enhancements.
Enhancements obtained when the player levels up fall into two categories: enhancing player character attributes and enhancing weapon attributes. Each upgrade randomly generates three enhancement choices, and the player selects one out of the three.

### 3.2 Global Enhancement System
Introduce a gold coin system, where the amount obtained per game is proportional to the time survived in the level.
By spending the gold coins collected in the level, players can globally enhance the basic attributes of all characters, weapon attributes, in-game gold coin acquisition coefficient, and the number of character revivals. Implement the above global enhancements, and you can customize more global enhancements.
Note that these are permanent enhancement bonuses that do not disappear at the end of a game.

### 3.3 Save and Load
In Phase One, we might have had to start the game anew each time it was opened. Now, the game should support save and load functionality. You only need to design a format to express the save, including global enhancements, level game state, etc. For demonstration, modify and load the save.

## 4. Technical Specifications: Phase Three
We have now completed a relatively complex survivor game. If you haven't implemented a GUI before, now is the time to add one. In addition, in this phase, there are some (easily implementable with GUI) practical features that need to be completed.

### 4.1 Displaying Unit Attack and Damage Effects
In Phase Two, we implemented the core logic of the game. However, if ranged units attack silently, melee units show no action during attacks, and units don't show any changes when taking damage, the health of both sides will quietly decrease. This can harm the gaming experience. Therefore, in Phase Three, we need to display the attack/damage effects of both units in the game interface:
- When units initiate or receive attacks, corresponding effects need to be drawn.
  - It doesn't have to play a whole animation; a simple flicker of the graphic representing the unit will do,
  - or you can display a number floating above its head, indicating how much damage the unit has taken,
  - or draw a health bar above its head.
  - Other ideas are also very welcome. In short, as long as it moves.

## 5. Technical Specifications: Phase Four
We have now created an "interesting" survivor game! To make it even more fun, this phase is an expansion phase, where you can simply add to the previous extension content or incorporate any cool ideas you have.
For example, you can add appropriate sound effects to the game. Functionally, you can design cool animations to enhance the user experience.
Feel free to add any ideas you find interesting!

# 1. 摘要
《吸血鬼幸存者》是2021年在Steam推出主打“割草”与“生存”概念的Roguelike游戏。游戏
推出后大受成功，在接下来的时间里引领了一股“幸存者”热潮，并成为了类幸存者游戏的先驱者。
让我们也来写一个类幸存者游戏吧！

## 2. 技术指标: 阶段一
我们参考已有的一些类幸存者游戏，制订了这份技术指标。本节介绍阶段一的要求。

### 2.1 地图
游戏的地图在逻辑上是一个 m × n 的矩形，存在边界。每个 1 × 1 的矩形是一个格子，敌
方单位从边缘格子随机刷新。格子可以共用，即多个单位可以处于同一个格子中。
你可以在地图中加一些可破坏/不可破坏的障碍物，敌我单位均不可以穿过障碍物。要求地
图上至少五个格子存在障碍物。

### 2.2 玩家
类幸存者游戏的玩家扮演幸存者，游戏目标是生存到规定时间，失败条件是到达规定时间前
死亡。
玩家操作角色的基础属性包括：生命值、攻击力、移动速度。
武器属性包括：伤害区域、持续时间、冷却时间。
你可以设定不同的角色，每个角色都有不同的基础属性，并持有一把独特的初始武器。要求
至少有两个角色供游玩选择。
玩家的操作十分简单，所有武器均为自动施放，在战斗中，玩家需要完成的输入仅有一种：
通过WASD控制移动。这里的“移动”在游戏逻辑上有两项作用：
1. 攻击目标，通过移动使武器伤害区域与敌人接触。
2. 躲避攻击，通过移动避免受到伤害。
如果实现了Extension 3.1掉落物，则移动会多一个作用：拾取物品，即通过移动使角色拾取
范围覆盖掉落物。

### 2.3 敌方单位
游戏中，玩家面对的唯一威胁来自持续不断生成并向玩家袭来的怪物狂潮。类幸存者游戏中
的敌方单位设计极为简单，绝大多数的普通怪物只有接触到玩家（处于相同地图格子）才可持续
造成伤害，少部分精英怪物能够远程攻击玩家（可以视为装备了武器）。
- 敌方单位：
  - 基础属性：生命值、攻击力、移动速度。
  - 出现方式：从屏幕边缘随机刷新。
  - 移动策略：持续像玩家方向移动、向固定方向移动且到达边界改变移动方向。
  - 攻击方式：近战（伤害区域为自身所在格子）、远程（可自定义伤害区域）。
要求至少实现一个近战单位一个远程单位，两种移动策略均需要实现。

## 3. 技术指标: 阶段二
我们已经完成了一个简单的类幸存者游戏！这听上去棒极了! 所以，让我们为这个游戏添加
更多的内容吧!游戏应当基于阶段一中已经完成的部分，只在确实有必要的情况下重构已有的代
码。

### 3.1 局内强化系统
关卡内的强化系统是类幸存者游戏最具代表性的特性之一。
新增设定：经验值、等级、强化。玩家击杀怪物获得经验值，经验值满足条件等级提升，等
级每提升一级玩家进行一次关卡内强化。
玩家升级获取的强化分为两种，一种提升玩家角色属性，一种提升武器属性，每次升级随机
产生三种强化选择，玩家进行三选一。

### 3.2 全局强化系统
增加金币设定，每局获得量与关卡中存活时间成正比。
通过消耗关卡中收集的金币，玩家可以在游戏主界面的商店中全局强化所有角色的基础属
性、武器属性、局内金币获取系数、角色复活次数等。要求实现以上全局强化内容，你也可以
自定义更多的全局强化内容。
注意，这是永久的强化加成，不会随着一局游戏的结束而消失。

### 3.3 存档的导入与导出
在阶段一中，我们可能每次打开游戏都要重新开始。现在，我们要能让游戏支持存档的导入
和导出。你只需为自己设计一套格式用来表达存档，包括全局强化、关卡游戏状态等，演示时修
改、加载存档即可。

## 4. 技术指标：阶段三
我们已经完成了一个比较复杂的类幸存者游戏，如果你前面没有实现GUI，那么现在是时候
加入GUI了。此外，在本阶段，还有一些(容易使用 GUI 实现的)实用功能需要完成。

### 4.1 展示单位的攻击和受伤效果
在阶段二中,我们实现了游戏的核心逻辑。但是,如果远程单位在攻击时一声不响,近战单位在
攻击时不展示任何动作,单位在受到攻击时也不会有任何变化,那么双方单位的血量就悄悄地减少
着。这就会损害游玩的体验。因此,在阶段三中,我们需要在游戏的界面中展示双方单位的攻击/受
伤效果:
- 单位发起、受到攻击时,需要绘制出相应的效果。
  - 不必播放一整段的动画,可以简单地把表示这个单位的图形闪烁一下,
  - 或者可以在它的头上飘一个数字,表示这个单位受到了多少伤害，
  - 又或者在头上绘制血条显示。
  - 非常欢迎其他的想法。总之,它只要动了就可以。

## 5. 技术指标：阶段四
我们已经完成了一个“有趣”的类幸存者游戏啦！为了让它更加的有趣，此阶段是扩展阶段，
你可以单纯按照前面的Extension内容来补充，也可以再加上任何你觉得很酷的想法。
比如，你可以为游戏添加适当的音效。从功能上讲，可以设计酷炫的动画来提升用户体验。
任何你觉得有趣的想法都可以加上来！
