#pragma once

/**
 * Internal ROM name. NEEDS TO BE **EXACTLY** 20 CHARACTERS. Can't be 19 characters, can't be 21 characters. You can fill it with spaces.
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
 * Also saves ID of the Jinjo that spawned the Jiggy for each world, so Jiggies can respawn at that Jinjo if you don't collect them.
 * Lastly, it
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
 * -Yum-Yum Crash
 * -Collectible Flag Radius Bug
 * -CCW Pink Jinjo Jiggy Despawn (Note: In vanilla, you can respawn the Jiggy by recollecting the Jinjos again, but with JINJO_SAVING enabled, the Jiggy can become permanently uncollectable)
 * -Incorrect BK Health Sprites
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
 * Allows you to skip the following cutscenes:
 * -Rareware Cutscene (Note: This is the very first cutscene you see when you boot up the game)
 * -Intro Cutscene
 * -Enter Lair Cutscene
 * -Game Over Cutscene
 * -Furnace Fun Parade
 * -Final Parade
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
 * Instead of holding L, R, and B to skip dialog, you can just press B.
 */
#define ONLY_B_BUTTON_SKIPS_DIALOG

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
 * Adds additional cheats to use, which are:
 * -"THIS CHEAT IS NO LIE RAISE THE WATER LEVEL VERY HIGH" - Raises the water level in Grunty's Lair to the 2nd level
 * -"THIS ONES SUCH A CHORE GET RID OF THE EIGHTH NOTE DOOR" - Unlocks the Eighth Note Door
 * -"GRUNTY YOU WILL DISPLEASE WHEN YOU OPEN HER DOOR WITH EASE" - Completes the Grunty picture and unlocks door of grunty
 *
 * -"THERES TOO MANY CHEATS TO NAME USE JUST ONE TO UNLOCK THE GAME" - Activates all Note Door Cheats, Complete Puzzle Cheats, Lair Progress Cheats, World Door Cheats, and Additional Cheats
 * (Note: Using this cheat will automatically trigger the text that will delete your save if you accept)
 *
 * NOTE: These codes also work with SHORTER_CHEATS enabled.
 */
#define ADDITIONAL_CHEATS
