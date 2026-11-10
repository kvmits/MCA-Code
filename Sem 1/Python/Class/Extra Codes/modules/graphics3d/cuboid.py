#Module to find the surface area and volume of a cuboid

def area(len, bre, hei):
    return 2 * (len * bre + bre * hei + hei * len)

def volume(len, bre, hei):
    return len * bre * hei