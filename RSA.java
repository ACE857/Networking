import java.io.UnsupportedEncodingException;
import java.math.BigInteger;
import java.security.InvalidKeyException;
import java.security.KeyFactory;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;
import java.util.Arrays;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;

public class RSA {


static String kPublic = "dmsxxhetzejiibz6z99xnjenpxzk8e9uu8kpj42b93gahqcjkwmlrtov4qhj1x1e2y5am212sjmk1ojt5yuv5xz7r9tggshuh4d0frzfy6lil40afkm8wibh2zbdr8m4e5izfmbfkbwngt3tzb2z3o9lnwg2jmtve5e1u04308y55pd6wd2mlsipqb4j9k7qhr3og0mw7xk5etbw3p4dy5hgan7wbaubxfohimljimalopll00w1c2zxatd";
static String kPrivate = "aftmhklqmrn01drhnjosgqbmj21zel7u5frf9mi8ziksx8fiszj3adbf5ku7ry2zm8mph4gigkr0gncz4job7oysjs8z09bxouoxkuqsmpjr1qsinmkfg6k7t9wx8qkppjdogsd98p4uzwyfie2rm6gzlgi4hhjaw4o4nrp6w4efioomx0yk8wvvpr3bftfkwz1o60xghq2ngeukwgz8r0lgf2j040se90j27lc465nv63y6j9bmwujp8so8i4p8aftaerrlji5o3g1muychwgpo9ukgzxxnp9w6gju9ryiepx2gp7lhth3ss59qjob6tu3574a89csxm17kesktjwlo7euwv4xcp3cl8hzqtt87hyrnebold92rvag33n33zsw6y5iz8trnm9vgrr5h2zer65zusunmlajwejayzwm5sm26aptfn1ezc35uysjiicttf8x6ill68m7k1w7ekm36swicmndl0brv1jab18x0oe9vbi9yojmvh2evwp4bujzsbe099qox82x8yk3uzqkqsj5os8fct43pw5mmdr4fjcmf93da0981w2mby8fhvlyssiz72400w0mz4whts5u1g8qmhdy4dlc1463peyrsaighvjeahiv7qzed5sp01rsbta3gk3dto3ejv2mctbq5q1zw246fnpb2pr7u3n49wvw312pmn9g7lsesvs2mrqn5b1v7sgdlrwmh53qxbbikclnxhai1s2ouiatpin89ny9o4njq0qh860giviz0j4307cu4kvun7mbjv5l5oy4xrdonwm70f2f48qlcn26g7hgv9t9634n2v2mrhyflk9vmyzowx63v1l0ed5ict97dm18et3ib0mobd5s8m9qjft9s0sjrxgre1uk7p3ws7vh7hqpn3t9yljz30z2st8ugxw0rwp57t7n4q1dc359s04fofut4hra8bb0pi2dg3czbw8m9krvc7f94t5me2zp";

public RSA()
{

}


public String Encrypt(String plain) throws NoSuchAlgorithmException,
        NoSuchPaddingException, InvalidKeyException,
        IllegalBlockSizeException, BadPaddingException {

    String encrypted;
    byte[] encryptedBytes;      
    PublicKey publicKey = null ;
    try{
        KeyFactory kf = KeyFactory.getInstance("RSA");
         byte[] encodedPb = stringToBytes(kPublic);
        X509EncodedKeySpec keySpecPb = new X509EncodedKeySpec(encodedPb);
        publicKey = kf.generatePublic(keySpecPb);
    }catch(Exception e){
            System.out.print(e.getMessage());
    }

    Cipher cipher = Cipher.getInstance("RSA");
    cipher.init(Cipher.ENCRYPT_MODE, publicKey);
    encryptedBytes = cipher.doFinal(plain.getBytes());

    encrypted = bytesToString(encryptedBytes);
    return encrypted;

}

public String Decrypt(String result) throws NoSuchAlgorithmException,
        NoSuchPaddingException, InvalidKeyException,
        IllegalBlockSizeException, BadPaddingException {

    byte[] decryptedBytes;

    byte[] byteKeyPrivate = stringToBytes(kPrivate);

    KeyFactory kf = KeyFactory.getInstance("RSA");

    PrivateKey privateKey = null;
    try {

        privateKey = kf.generatePrivate(new PKCS8EncodedKeySpec(byteKeyPrivate));

    } catch (InvalidKeySpecException e) {
        e.printStackTrace();
    }

    String decrypted;

    Cipher cipher = Cipher.getInstance("RSA");
    cipher.init(Cipher.DECRYPT_MODE, privateKey);
    decryptedBytes = cipher.doFinal(stringToBytes(result));
    decrypted = new String(decryptedBytes);
    return decrypted;

}

public String bytesToString(byte[] b) {
    byte[] b2 = new byte[b.length + 1];
    b2[0] = 1;
    System.arraycopy(b, 0, b2, 1, b.length);
    return new BigInteger(b2).toString(36);
}

public byte[] stringToBytes(String s) {
    byte[] b2 = new BigInteger(s, 36).toByteArray();
    return Arrays.copyOfRange(b2, 1, b2.length);
}

public static void main(String[] args) {

	try{
		RSA r = new RSA();
		String msg = "qwertyuiopasdfghjklzxcvbnm7418520963/*-+.!@#$%^&*()_+";
		String e = r.Encrypt(msg);
		System.out.print("\n\nmessage is "+msg+"\nEncrypted msg "+e);
		String d = r.Decrypt(e);
		System.out.print("\n\n\nde is "+d);
		System.out.print("\n\n"+d.equals(msg));
		System.out.print("\n\nPublicKey "+RSA.kPublic);
		System.out.print("\n\nPrivateKey "+RSA.kPrivate);
	}
	catch(Exception e){
		System.out.print(e.getMessage());
	}
        
    }

}

