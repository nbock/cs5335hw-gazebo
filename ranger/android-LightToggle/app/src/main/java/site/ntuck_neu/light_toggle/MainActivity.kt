package site.ntuck_neu.light_toggle

import android.content.Context
import android.hardware.usb.UsbManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.CompoundButton
import android.widget.Switch
import android.widget.TextView
import com.hoho.android.usbserial.driver.UsbSerialPort
import com.hoho.android.usbserial.driver.UsbSerialProber

class MainActivity : AppCompatActivity(), CompoundButton.OnCheckedChangeListener {
    private var port: UsbSerialPort? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val sw = findViewById<Switch>(R.id.switch1)
        sw.setOnCheckedChangeListener(this)

        openSerial()
    }

    override fun onCheckedChanged(_btn: CompoundButton?, checked: Boolean) {
        val text1 = findViewById<TextView>(R.id.text1)
        if (checked) {
            text1.setText("on")
            port?.write("on\n".toByteArray(), 100)
        }
        else {
            text1.setText("off")
            port?.write("off\n".toByteArray(), 100)
        }
    }

    // https://github.com/mik3y/usb-serial-for-android
    // ref: example code
    fun openSerial() {
        val mgr = getSystemService(Context.USB_SERVICE) as UsbManager
        val drivers = UsbSerialProber.getDefaultProber().findAllDrivers(mgr)
        if (drivers.isEmpty()) {
            return
        }

        val drv = drivers[0]
        val conn = mgr.openDevice(drv.device)
        if (conn == null) {
            val text1 = findViewById<TextView>(R.id.text1)
            text1.setText("need permission")
            mgr.requestPermission(drv.getDevice(), null)
        }

        port = drv.ports[0]
        port?.open(conn);
        port?.setParameters(9600, 8, UsbSerialPort.STOPBITS_1, UsbSerialPort.PARITY_NONE)
    }
}