#pragma once

/**
 * Internal ROM name. NEEDS TO BE **EXACTLY** 20 CHARACTERS. Can't be 19 characters, can't be 21 characters. You can fill it with spaces.
 * If left undefined, the default ROM name will be "Banjo-Kazooie".
 * The end quote should be here:               "
 */
#define INTERNAL_ROM_NAME "Banjo-Kazooie QOL   "

/**
 * Removes the anti-piracy functionality that makes Banjo slide in TTC.
 * Doesn't remove the checks that delete moves or the bridge in SM since they have yet to be triggered by any changes so far.
 */
#define REMOVE_ANTI_PIRACY_CHECK

/**
 * Extends save files so extra data can be saved. Also changes header so some emulators and Everdrive can automatically detect 16k Eeprom.
 *
 * NOTE: MUST BE ON SO NOTE SAVING AND JINJO SAVING CAN SAVE PROPERLY.
 */
#define EEPROM_16K

/**
 * Saves collected Notes so you don't have to recollect them.
 *
 * Note: EEPROM_16K must be on to save properly.
 */
#define NOTE_SAVING

/**
 * Saves collected Jinjos so you don't have to recollect them.
 * Also saves the ID of the Jinjo that spawned the Jiggy for each world, so Jiggies can respawn at that Jinjo if you don't collect them.
 *
 * Note: EEPROM_16K must be on to save properly.
 */
#define JINJO_SAVING

/**
 * Lets you add 9th Honeycomb to health bar. Total health, including Double Health, can be up to 18.
 * Also changes how double health works. Instead of giving the player maximum health, it simply doubles current health total. Any health upgrades you get after will add 2 health to your total.
 *
 * Note: The 9th Honeycomb partially covers the Note sprite in the pause menu.
 */
#define HEALTH_SYSTEM_REWORK

/**
 * Fixes the following bugs:
 * -Jinjo Statue Softlock
 * -Yum-Yum Crash
 * -Collectible Flag Radius Bug
 * -CCW Pink Jinjo Jiggy Despawn (Note: In vanilla, you can respawn the Jiggy by recollecting the Jinjos again, but with JINJO_SAVING enabled, the Jiggy can become permanently uncollectable)
 * -Incorrect BK Health Sprites
 * -Max Health Cheat Temporarily Removes Double Defense (Note: HEALTH_SYSTEM_REWORK also fixes this bug)
 * -Minor Game Over Cutscene Issues (Note: SKIPPABLE_CUTSCENES also fixes these issues)
 */
#define BUG_FIXES

/**
 * Fixes the following vanilla specific bugs:
 * -MMM Loggo & Cellar Token ID
 * -"Collectible Flag Radius Bug" Fix for Mumbo Tokens only (Note: Due to the way some flags and items are positioned in the vanilla game, this bug is necessary for some flags to set properly)
 *
 * Note: These fixes are hardcoded with the vanilla game in mind.
 */
#define VANILLA_SPECIFIC_BUG_FIXES

/**
 * Camera is slightly better. Doesn't drastically change angles when rotating around level geometry.
 */
#define BETTER_CAMERA

/**
 * Ignores any objects that alter the framerate.
 * There are several objects in the game that change the framerate. If the game finds any of these objects in a map, then it changes the FPS depending on what the object ID is.
 * They can be found in the Concert Cutscene, Gobi's Valley Lobby, and the First Ending Beach Cutscene.
 * IGNORE_FRAMERATE_ALTERING_OBJECTS removes any functionality that changes the FPS. All maps now run at 30 FPS.
 *
 * NOTE: This change has some unintentional side effects:
 *       -Some sound effects in the Concert Cutscene have slightly different timing
 *       -You can't clip inside the coffin to get the GV Witch Switch Jiggy early
 *       -The moving Shock Jump Spring Pad in Gobi's Valley Lobby moves faster
 *       -The dialog in the First Ending Beach Cutscene runs slightly faster
 */
#define IGNORE_FRAMERATE_ALTERING_OBJECTS

/**
 * Allows you to skip the following cutscenes:
 * -Rareware Cutscene (Note: This is the very first cutscene you see when you boot up the game)
 * -Intro Cutscenes (Note: The vanilla game requires you to have at least one save file to skip this cutscene. This requirement is removed.)
 * -Enter Lair Cutscene (Note: The vanilla game requires you to have viewed the cutscene at least once in any save file to skip it. This requirement is removed.)
 * -Game Over Cutscene (Note: The vanilla game requires you to have viewed the cutscene at least once in the current save file to skip it. This requirement is removed.)
 * -Winning Furnace Fun Cutscene
 * -Furnace Fun Parade
 * -Mumbo's Barbeque Cutscene
 * -Grunty Falling Cutscenes
 * -Ending Beach Cutscenes
 * -Final Parade
 * -Stop 'N' Swop Picture Cutscenes
 * -The End Cutscenes
 * 
 * Also fixes some minor issues with the Game Over Cutscene.
 */
#define SKIPPABLE_CUTSCENES

/**
 * Reimplements Exit To Witch's Lair option in the pause menu.
 * Cannot use it if you're not in a level.
 *
 * Note: Grunty's hat will cover Banjo's head in the pause menu.
 */
#define REIMPLEMENT_EXIT_TO_WITCHS_LAIR

/**
 * When you use Talon Trot or Wonderwing, you don't need to hold Z to keep using them. To exit, you can press Z or B.
 */
#define DONT_HOLD_Z_TO_USE_MOVES

/**
 * Instead of holding L, R, and B to skip dialog, you can just press B.
 */
#define ONLY_B_BUTTON_SKIPS_DIALOG

/**
 * Unlock the ability to place all Jiggies in a picture before Bottles tells you.
 */
#define UNLOCK_PLACE_ALL_PUZZLE_PIECES

/**
 * The Sand Castle becomes permanently drained when you collect the Sand Castle Jiggy.
 */
#define SAND_CASTLE_PERMANENTLY_DRAINED

/**
 * Lowers the Mumbo Token Inside the Water Pyramid in Gobi's Valley when you collect the Jiggy and lower the water level.
 */
#define LOWER_MUMBO_TOKEN_INSIDE_WATER_PYRAMID

/**
 * Adds a volatile flag to the Clucker Cutscene so you don't have to rewatch it when you leave the level.
 * Resets when you "Save and Quit" or reset the game.
 */
#define CLUCKER_CUTSCENE_VOLATILE_FLAG

/**
 * Abbreviates most sandcastle cheat codes.
 * Example: "BANJO BEGS FOR PLENTY OF EGGS" -> "BBFPOE"
 *
 * NOTE: This mainly applies to banned cheat codes. The "BANJOKAZOOIE" code, "EIOOZAKOJNAB" code, as well as the cheat codes from Cheato, Bottles, and Stop n' Swop ARE NOT SHORTENED.
 */
#define SHORTER_CHEATS

/**
 * Plays the moo sound effect for all banned cheats and Stop n' Swop codes instead of just the "CHEAT" code.
 * Also resets the cheat progress so you can reinput the cheat right away, instead of having to reenter the sandcastle.
 */
#define EASIER_CHEATS

/**
 * Lets you enter more than 3 banned cheat codes even after Grunty erases your save.
 */
#define ENTER_MORE_THAN_3_BANNED_CHEATS

/**
 * Reworks the save flags for banned cheats. Instead of each cheat having their own individual flag (most of which will go unused), save the indexes of whatever cheats were used.
 * Only two cheats can be saved per file. 6 bits are used for each cheat (which can technically allow up to 63 different cheats to be saved, but you are limited to how many volatile flags there are).
 */
#define CHEAT_FLAGS_REWORK

/**
 * Adds additional cheats to use, which are:
 * -"THIS CHEAT IS NO LIE RAISE THE WATER LEVEL VERY HIGH" - Raises the water level in Grunty's Lair to the 2nd level
 * -"THIS ONES SUCH A CHORE GET RID OF THE EIGHTH NOTE DOOR" - Unlocks the Eighth Note Door
 * -"GRUNTY YOU WILL DISPLEASE WHEN YOU OPEN HER DOOR WITH EASE" - Completes the Grunty picture and unlocks Door of Grunty
 * -"ALL THE CAULDRONS YOU WILL WAKE LITTLE EFFORT IT WILL TAKE" - Unlock all Cauldrons
 * -"BANJOS GOT HIS GROOVE NOW THAT HES LEARNED EVERY MOVE" - Unlock all abilities
 * -"MANY TREASURES ARE NOW YOURS UNLOCK THE LAST FOUR NOTE DOORS" - Unlocks the Four Note Doors in the room with Dingpot
 * -"YOULL STAY OUT OF TROUBLE WHEN YOUR HEALTH IS DOUBLE" - Gives Double Health Upgrade
 * (Note: These cheats are banned, which means if you input three of them, your save file will be erased)
 *
 * -"THERES TOO MANY CHEATS TO NAME USE JUST ONE TO UNLOCK THE GAME" - Activates all Note Door Cheats, Complete Puzzle Cheats, Lair Progress Cheats, World Door Cheats, and the Additional Cheats listed above
 * (Note: Using this cheat will automatically trigger the text that will delete your save if you accept)
 *
 * -"YOU MUST LOVE THIS GAME A TON IF YOU WANT TO REPLAY FURNACE FUN" - Lets you replay Grunty's Furnace Fun
 * -"GRUNTY YOU MUST DISPATCH IF YOU WANT A REMATCH" - Lets you refight the Final Boss
 * (Note: These cheats aren't banned, so input them as many times as you like)
 *
 * NOTE: CHEAT_FLAGS_REWORK must be on to save properly.
 * Note: These codes also work with SHORTER_CHEATS enabled.
 */
#define ADDITIONAL_CHEATS



// EXPERIMENTAL DEFINES //

/**
 * Switches the Stop 'N' Swop item keys so that the game can recieve Stop 'N' Swop data from vanilla Banjo-Kazooie. The game also outputs data that vanilla Banjo-Kazooie can recieve.
 * This means Stop 'N' Swop technically works now, however all this does is unlock the Eggs and Ice Key without inputting the sandcastle cheat codes.
 */
// #define STOP_N_SWOP_FUNCTIONALITY

/**
 * Alters the default framerate of the game.
 * While more complicated than this, calculating the framerate can be understood as dividing 60 by X, meaning the max framerate is 60 and the minimum is virtually 0.
 * DEFAULT_FRAMERATE_MODIFIER is essentially just X, which means you can plug in a number to change the framerate. 1 is 60 FPS, 2 is 30 FPS, 3 is 20 FPS, etc.
 * 
 * NOTE: Changing the framerate also changes the physics of many objects as well. May cause some problems throughout the game.
 * NOTE: There are objects in the game that can change the framerate, such as the one in Gobi's Valley Lobby. These objects will take priority over DEFAULT_FRAMERATE_MODIFIER.
 *       Use IGNORE_FRAMERATE_ALTERING_OBJECTS to be able to change the framerate in all maps.
 * Note: Default is 2 (30 FPS).
 */
// #define DEFAULT_FRAMERATE_MODIFIER 2

/**
 * Changes how fast game logic is executed. Can be used to speed up or slow down gameplay.
 * Anything greater than 1.0f will speed the game up. Any number in between 0 and 1 will slow it down.
 * 
 * NOTE: Changing the delta time also changes the physics of many objects as well. May cause some problems throughout the game,
 *       ESPECIALLY when the value is set too high and the game won't work when it's set to less than or equal to 0.
 * NOTE: While never used in game, the function time_setMultiplier() can also be used to alter delta time. Any changes made with time_setMultiplier() will take priority over DEFAULT_TIME_MULTIPLIER.
 *       The other function time_reset() can be used to reset to default values.
 * Note: Default is 1.0f.
 */
// #define DEFAULT_TIME_MULTIPLIER 1.0f
