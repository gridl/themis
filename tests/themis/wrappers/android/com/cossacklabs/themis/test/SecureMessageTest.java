package com.cossacklabs.themis.test;

import java.util.Arrays;
import java.util.Random;

import com.cossacklabs.themis.KeyGenerationException;
import com.cossacklabs.themis.Keypair;
import com.cossacklabs.themis.KeypairGenerator;
import com.cossacklabs.themis.NullArgumentException;
import com.cossacklabs.themis.SecureMessage;
import com.cossacklabs.themis.SecureMessageWrapException;

import android.test.AndroidTestCase;

public class SecureMessageTest extends AndroidTestCase {
	
	@Override
	public void runTest() {
		
		Keypair aPair = null;
		Keypair bPair = null;
		
		try {
			aPair = KeypairGenerator.generateKeypair();
			bPair = KeypairGenerator.generateKeypair();
		} catch (KeyGenerationException e) {
			fail("Failed to generate keypairs");
		}
		
		assertNotNull(aPair);
		assertNotNull(bPair);

		Random rand = new Random();
		
		int messageLength = 0;
		
		do {
			messageLength = rand.nextInt(2048);
		} while (0 == messageLength);
		
		byte[] message = new byte[messageLength];
		rand.nextBytes(message);
		
		try {
			SecureMessage aWrapper = new SecureMessage(aPair.getPrivateKey(), bPair.getPublicKey());
			SecureMessage bWrapper = new SecureMessage(bPair.getPrivateKey(), aPair.getPublicKey());
			
			byte[] wrappedMessage = aWrapper.wrap(message);
			
			assertTrue(message.length < wrappedMessage.length);
			
			byte[] unwrappedMessage = bWrapper.unwrap(wrappedMessage);
			
			assertTrue(Arrays.equals(message, unwrappedMessage));
		} catch (NullArgumentException e) {
			fail(e.getClass().getCanonicalName() + ": " + e.getMessage());
		} catch (SecureMessageWrapException e) {
			fail(e.getClass().getCanonicalName());
		}
	}
}