import qrcode
from PIL import Image
import os
 
def make_qr(str,save):
    qr=qrcode.QRCode(
        version=None,  #image size 1-40  1:21*21(21+(n-1)*4)
        error_correction=qrcode.constants.ERROR_CORRECT_M, #L:7% M:15% Q:25% H:30%
        box_size=10, #pix size
        border=2, #border width
    )
    qr.add_data(str)
    qr.make(fit=True)
 
    img=qr.make_image()
    img.save(save)
 
 
def make_logo_qr(str,logo,save):
    qr=qrcode.QRCode(
        version=None,
        error_correction=qrcode.constants.ERROR_CORRECT_M,
        box_size=10,
        border=2
    )
    qr.add_data(str)
    qr.make(fit=True)

    img=qr.make_image()
    img=img.convert("RGBA")
 
    #add logo
    if logo and os.path.exists(logo):
        icon=Image.open(logo)
        img_w,img_h=img.size
 
        factor=4
        size_w=int(img_w/factor)
        size_h=int(img_h/factor)
 
        icon_w,icon_h=icon.size
        if icon_w>size_w:
            icon_w=size_w
        if icon_h>size_h:
            icon_h=size_h
        icon=icon.resize((icon_w,icon_h),Image.ANTIALIAS)
 
        w=int((img_w-icon_w)/2)
        h=int((img_h-icon_h)/2)
        icon=icon.convert("RGBA")
        img.paste(icon,(w,h),icon)
 
    img.save(save)
 
 
if __name__=='__main__':
    save_path='theqrcode.png' 
    #logo='logo.jpg' 

    src = "www.xxiong.me"
    make_qr(src, "abc.png")
 
    #make_logo_qr(src,"logo.png","xxiong.me.logo.png")
