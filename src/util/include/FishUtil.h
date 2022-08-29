/**
 * @file FishUtil.h
 * Strategy for ><> commands.
 * @author Conlan Wesson
 */

#pragma once

/**
 * Check if a stack exists.
 * @param _s Stack index.
 * @warning Returns ERROR_UNSPEC from the current function if the check fails.
 */
#define check_selected(_s) if((_s) >= stack.size()) { return ERROR_UNSPEC; }


/**
 * Check if a stack exists and has enough elements.
 * @param _s Stack index.
 * @param _n Number of elements.
 * @warning Returns ERROR_UNSPEC from the current function if the check fails.
 */
#define check_stack(_s, _n) if((_s) >= stack.size() || stack.at(_s).size() < (_n)) { return ERROR_UNSPEC; }
