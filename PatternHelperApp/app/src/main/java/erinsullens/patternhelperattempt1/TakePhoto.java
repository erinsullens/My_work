package erinsullens.patternhelperattempt1;

import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Pair;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

import java.io.ByteArrayOutputStream;
import java.io.IOException;

public class TakePhoto extends AppCompatActivity {
    static final int REQUEST_IMAGE_CAPTURE = 11111;
    private Bitmap imageBitmap;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_take_photo);
        Button btnPhoto = ((Button) (findViewById(R.id.photoButton)));

        btnPhoto.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                displayCamera();
            }
        });

        Button btnSave = ((Button) (findViewById(R.id.sharePhoto)));
        btnSave.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                share();
            }

        });
    }

    public void share(){
        new EndpointsAsyncTask().execute(new Pair<Context, String>(this, "asdf"));

    }


    private byte[] getBytes(Bitmap bitmap) {
        if (bitmap == null || bitmap.getWidth() == 0 || bitmap.getHeight() == 0)
            return null;

        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        try {
            bitmap.compress(Bitmap.CompressFormat.JPEG, 90, bos);
            bos.flush();
            bos.close();
        } catch (IOException ioe) {
            return null;
        }

        byte[] bytes = bos.toByteArray();
        return bytes != null && bytes.length > 0 ? bytes : null;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == REQUEST_IMAGE_CAPTURE && resultCode == RESULT_OK) {
            // when camera returns
            Bundle extras = data.getExtras();
            imageBitmap = (Bitmap) extras.get("data");
            ImageView imgView = ((ImageView) findViewById(R.id.imageView2));
            imgView.setImageBitmap(imageBitmap);
        }

        // note that the method of saving images shown on
        // http://developer.android.com/training/camera/photobasics.html is
        // buggy on some devices, but we can get the byte[] directly, as shown
        // below
    }


    private void displayCamera() {
        Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        if (takePictureIntent.resolveActivity(getPackageManager()) != null) {
            startActivityForResult(takePictureIntent, REQUEST_IMAGE_CAPTURE);
        }
    }
}
