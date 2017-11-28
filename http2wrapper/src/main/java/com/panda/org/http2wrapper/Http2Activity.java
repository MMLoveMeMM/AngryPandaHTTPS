package com.panda.org.http2wrapper;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class Http2Activity extends Activity {

    private Button mDohttpBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_http2);

        mDohttpBtn=(Button)findViewById(R.id.dohttp2);
        mDohttpBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Http2Core.dohttp2();
            }
        });

    }
}
