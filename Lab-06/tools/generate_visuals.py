"""Create small, dependency-free animated GIFs for the Lab-06 README."""
from pathlib import Path
import struct

W, H = 480, 260
PALETTE = [(13,18,34),(24,33,55),(225,232,245),(57,73,105),(70,190,170),(96,165,250),(251,191,36),(244,114,182),(167,139,250),(52,211,153),(248,113,113),(148,163,184),(14,116,144),(21,128,61),(161,98,7),(159,18,57)]
BG, PANEL, INK, MUTED, TEAL, BLUE, GOLD, PINK, PURPLE, GREEN, RED, GREY = range(12)

def canvas(): return [BG] * (W * H)
def rect(p, x, y, width, height, color):
    x0, x1 = max(0,x), min(W,x+width)
    for yy in range(max(0,y), min(H,y+height)): p[yy*W+x0:yy*W+x1] = [color] * max(0,x1-x0)
def frame_base(p, accent):
    rect(p,18,18,W-36,H-36,PANEL); rect(p,18,18,W-36,6,accent)
    rect(p,34,42,120,8,INK); rect(p,34,58,76,5,MUTED)

def gif_lzw(indices, minimum_code_size=4):
    """GIF LZW coding, packed least-significant-bit first."""
    clear, end = 1 << minimum_code_size, (1 << minimum_code_size) + 1
    table = {bytes([i]): i for i in range(clear)}
    code_size, next_code, stream, accumulator, bits = minimum_code_size+1, end+1, bytearray(), 0, 0
    def emit(code, size):
        nonlocal accumulator, bits
        accumulator |= code << bits; bits += size
        while bits >= 8: stream.append(accumulator & 255); accumulator >>= 8; bits -= 8
    emit(clear, code_size); word = bytes([indices[0]])
    for value in indices[1:]:
        candidate = word + bytes([value])
        if candidate in table: word = candidate; continue
        emit(table[word], code_size)
        if next_code < 4096:
            table[candidate] = next_code; next_code += 1
            if next_code == (1 << code_size) and code_size < 12: code_size += 1
        else:
            emit(clear, code_size); table = {bytes([i]): i for i in range(clear)}; code_size, next_code = minimum_code_size+1, end+1
        word = bytes([value])
    emit(table[word], code_size); emit(end, code_size)
    if bits: stream.append(accumulator & 255)
    return bytes(stream)

def write_gif(path, frames, delay_cs=9):
    raw = bytearray(b"GIF89a") + struct.pack("<HHBBB", W,H,0xF3,0,0)
    for r,g,b in PALETTE: raw += bytes((r,g,b))
    raw += b"!\xFF\x0BNETSCAPE2.0\x03\x01\x00\x00\x00"
    for pixels in frames:
        raw += b"!\xF9\x04\x00" + struct.pack("<H",delay_cs) + b"\x00\x00"
        raw += b"," + struct.pack("<HHHHB",0,0,W,H,0)
        data = gif_lzw(pixels); raw += b"\x04"
        for i in range(0,len(data),255): raw += bytes((min(255,len(data)-i),)) + data[i:i+255]
        raw += b"\x00"
    path.write_bytes(raw + b";")

def array_frames():
    values, frames = [3,8,5,1,7,4,6,2], []
    for step in range(16):
        p=canvas(); frame_base(p,TEAL); rect(p,34,208,412,3,MUTED)
        ordered=values if step<4 else sorted(values); highlight=step % len(values)
        for i,value in enumerate(ordered):
            rect(p,58+46*i,208-value*16,28,value*16,GOLD if i==highlight else TEAL); rect(p,58+46*i,216,28,7,INK)
        rect(p,34,82,180+(step%9)*24,12,BLUE); rect(p,34,110,250,8,MUTED); frames.append(p)
    return frames

def matrix_frames():
    frames=[]
    for step in range(16):
        p=canvas(); frame_base(p,PURPLE)
        for i in range(6):
            for j in range(6): rect(p,80+43*j,82+22*i,35,16,PURPLE if (i,j)==(step%6,(step//2)%6) else BLUE if i==j else MUTED)
        rect(p,350,86,55,110+(step%5)*11,GOLD); rect(p,34,222,370,8,TEAL); frames.append(p)
    return frames

def fft_frames():
    frames=[]
    for step in range(16):
        p=canvas(); frame_base(p,GOLD)
        for i in range(8):
            rect(p,45+i*42,86,26,18,BLUE if (i+step)%3 else TEAL); rect(p,45+i*42,126,26,18,PURPLE if (i+step)%2 else PINK)
            if i <= step%9: rect(p,45+i*42,204-(i%4)*16,26,(i%4)*16+12,GOLD)
        for i in range(7): rect(p,70+i*42,108,3,18,INK)
        rect(p,34,164,380,4,TEAL); frames.append(p)
    return frames

def reversal_frames():
    original, frames = [PINK,BLUE,GOLD,PURPLE,TEAL,RED,GREEN,BLUE], []
    for step in range(16):
        p=canvas(); frame_base(p,PINK); row=original if step<5 else sorted(original)
        for i,color in enumerate(row): rect(p,48+i*46,124,36,42,color)
        left,right=step%5,min(7,step%5+3); rect(p,48+left*46,113,(right-left+1)*46-10,5,INK); rect(p,48+left*46,173,(right-left+1)*46-10,5,INK)
        rect(p,48+left*46,113,5,65,INK); rect(p,48+right*46+31,113,5,65,INK); rect(p,34,210,55+step*20,8,TEAL); frames.append(p)
    return frames

def main():
    out=Path(__file__).resolve().parents[1]/"visuals"; out.mkdir(exist_ok=True)
    for name,frames in (("array-operations.gif",array_frames()),("matrix-operations.gif",matrix_frames()),("fft-convolution.gif",fft_frames()),("reversal-sort.gif",reversal_frames())):
        write_gif(out/name,frames); print("wrote",out/name)
if __name__ == "__main__": main()
