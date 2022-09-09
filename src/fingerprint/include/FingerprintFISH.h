/**
 * @file FingerprintFISH.h
 * Some common ><> and *><> commands.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintFISH : public Fingerprint {
	public:
		explicit FingerprintFISH(FungeRunner& r);
		virtual ~FingerprintFISH() = default;
		
		virtual FungeError execute(inst_t cmd) override;

		virtual void activate() override;
	
	protected:
		enum {
			FISHER_UP,
			FISHER_DOWN,
		} fisherstate;

		Vector fishercache;

		void fishermanChange(const Vector& delta);
};

}
