package com.panda.org.angrypandaopenssl;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

import com.panda.org.http2wrapper.Http2Activity;

import java.text.SimpleDateFormat;
import java.util.Calendar;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);

        Calendar calendar = Calendar.getInstance();
        System.out.println("Start Time : " + new SimpleDateFormat("yyyy-MM-dd HH:mm:ss:SSS").format(calendar.getTime()));
        OpensslCore.generateKey();
        calendar = Calendar.getInstance();
        System.out.println("End Time : " + new SimpleDateFormat("yyyy-MM-dd HH:mm:ss:SSS").format(calendar.getTime()));
        // 原始字符串
        String originalText = "hello world, 0，  你好!";
        // 直接加密后的byte数组
        byte[] originalBytes = OpensslCore.rsaEncrypt(originalText.getBytes());
        // 内部生成的公钥
        String publicKey = OpensslCore.getPublicKey();
        // 根据原始字符串直接还原出的字符串
        String restoreText = new String(OpensslCore.rsaDecrypt(originalBytes));
        // 用外部输入公钥加密后的byte数组
        byte[] encryptTextBytes = OpensslCore.rsaEncryptByExtPublicKey(originalText.getBytes(), publicKey);
        String restoreTextByExtPublicKey = new String(OpensslCore.rsaDecrypt(encryptTextBytes));

        String builder = "原始字符串 :\n" +
                originalText +
                "\n" +
                "\n" +
                "公钥 :\n" +
                publicKey +
                "\n" +
                "直接还原字符串 :\n" +
                restoreText +
                "\n" +
                "\n" +
                "使用外部公钥还原字符串 :\n" +
                restoreTextByExtPublicKey +
                "\n";

        OpensslCore.releaseKey();
        tv.setText(builder);

    }

    @Override
    protected void onResume() {
        super.onResume();

        Intent intent = new Intent();
        intent.setClass(MainActivity.this, Http2Activity.class);
        this.startActivity(intent);

    }
}
