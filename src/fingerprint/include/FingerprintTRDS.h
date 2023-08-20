/**
 * @file FingerprintTRDS.h
 * IP travel in time and space.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintTRDS : public Fingerprint {
	public:
		explicit FingerprintTRDS(FungeRunner& r);
		virtual ~FingerprintTRDS() = default;
		
		virtual FungeError execute(inst_t cmd) override;
	
	private:
		enum relativity {
			NONE,
			ABSOLUTE,
			RELATIVE
		};

		Vector space;
		relativity space_rel;
		ssize_t time;
		relativity time_rel;
		Vector vec;
		relativity vec_rel;
		Vector jump_space;
		ssize_t jump_time;
		Vector jump_vec;
		bool jumping;
};

}
