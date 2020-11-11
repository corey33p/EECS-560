from PIL import Image, ImageDraw,ImageFont
from math import pi
import math
import numpy as np

def getXY(im_size,node_num,node_count):
    angle = 2*pi/node_count
    theta = node_num*angle
    x=.45*im_size[0]*math.cos(theta)+.5*im_size[0]
    y=.45*im_size[1]*math.sin(theta)+.5*im_size[1]
    return x,y

def shrink_line(x1,y1,x2,y2,factor = .9):
    delta_x = x2-x1
    delta_y = y2-y1
    factor_half = 1 - (1 - factor) / 2
    x1=x1+factor_half*delta_x
    y1=y1+factor_half*delta_y
    x2=x2-factor_half*delta_x
    y2=y2-factor_half*delta_y
    return x1,y1,x2,y2

def make_nodes(im,n):
    draw = ImageDraw.Draw(im)
    font_size = 45
    font = ImageFont.truetype('FreeMono.ttf', size=font_size)
    color = 'rgb(255,255,255)'
    for i in range(n):
        x,y=getXY(im.size,i,n)
        # draw.text((x-.02*im.size[0],y-.02*im.size[0]),str(i),fill=color,font=font,anchor="middle")
        draw.text((x-font_size/2,y-font_size/2),str(i),fill=color,font=font,anchor="middle")
    return im

def place_weight(draw,line_loc,weight):
    font_size = 16
    font = ImageFont.truetype('FreeMono.ttf', size=font_size)
    color = 'rgb(255,255,255)'
    delta_x = line_loc[2]-line_loc[0]
    delta_y = line_loc[3]-line_loc[1]
    new_x = line_loc[0]+.9*delta_x
    new_y = line_loc[1]+.9*delta_y
    new_x = new_x - font_size / 2
    new_y = new_y - font_size / 2
    draw.text((new_x,new_y),str(int(weight)),fill=color,font=font,anchor="middle")
    return draw

def draw_arrow(draw,line_loc,im_size):
    draw.line(line_loc)
    delta_x = line_loc[2]-line_loc[0]
    delta_y = line_loc[3]-line_loc[1]
    if delta_x == 0:
        theta = pi/2
    else:
        theta = math.atan(delta_y/delta_x)
    theta_1 = theta - pi/4
    theta_2 = theta + pi/4
    head_length = im_size[0]/50
    flip = False
    # if delta_x <= 0 and delta_y < 0: flip = True
    # if delta_x <= 0 and delta_y > 0: flip = True
    if delta_x <= 0: flip = True
    if flip:
        arrowhead_1_coords = line_loc[0],line_loc[1],line_loc[0]-head_length*math.cos(theta_1),line_loc[1]-head_length*math.sin(theta_1)
        arrowhead_2_coords = line_loc[0],line_loc[1],line_loc[0]-head_length*math.cos(theta_2),line_loc[1]-head_length*math.sin(theta_2)
    else:
        arrowhead_1_coords = line_loc[0],line_loc[1],line_loc[0]+head_length*math.cos(theta_1),line_loc[1]+head_length*math.sin(theta_1)
        arrowhead_2_coords = line_loc[0],line_loc[1],line_loc[0]+head_length*math.cos(theta_2),line_loc[1]+head_length*math.sin(theta_2)
    # print("arrowhead_1_coords: "+str(arrowhead_1_coords))
    # print("arrowhead_2_coords: "+str(arrowhead_2_coords))
    draw.line(arrowhead_1_coords)
    draw.line(arrowhead_2_coords)
    return draw

def offset_line(line_loc,im_size):
    scoot_factor = .008*im_size[0]
    x1,y1,x2,y2 = line_loc
    delta_x = x2-x1
    delta_y = -(y2-y1)
    if delta_x == 0:
        perpendicular_slope = 'inf'
    else:
        perpendicular_slope = -delta_x / delta_y
    if perpendicular_slope == 'inf':
        if y2 < y1:
            y1+=scoot_factor
            y2+=scoot_factor
        else:
            y1-=scoot_factor
            y2-=scoot_factor
    else:
        x1+= scoot_factor * delta_y * .001
        x2+= scoot_factor * delta_y * .001
        y1+= scoot_factor * delta_x * .001
        y2+= scoot_factor * delta_x * .001
        # if x1 < x2:
        #     x1+= scoot_factor * math.cos(perpendicular_slope)
        #     x2+= scoot_factor * math.cos(perpendicular_slope)
        #     y1+= scoot_factor * math.sin(perpendicular_slope)
        #     y2+= scoot_factor * math.sin(perpendicular_slope)
        # else:
        #     x1-= scoot_factor * math.cos(perpendicular_slope)
        #     x2-= scoot_factor * math.cos(perpendicular_slope)
        #     y1+= scoot_factor * math.sin(perpendicular_slope)
        #     y2+= scoot_factor * math.sin(perpendicular_slope)
    return x1,y1,x2,y2

def make_edges(im,num_nodes,edges):
    draw = ImageDraw.Draw(im)
    for edge in edges:
        x1,y1 = getXY(im.size,edge[0],num_nodes)
        x2,y2 = getXY(im.size,edge[1],num_nodes)
        line_loc = shrink_line(x1,y1,x2,y2)
        line_loc = offset_line(line_loc,im.size)
        draw_arrow(draw,line_loc,im.size)
        draw = place_weight(draw,line_loc,edge[2])
        # im.save("out.png")
        # input("check")
    return im

def read_file(file):
    f = open(file,"r")
    data = f.read()
    data = data.split(",")
    if data[-1]=='': data.pop(-1) # get rid of empty element
    ar_len = int(len(data)/3)
    assert(ar_len%1==0)
    edges_ar = np.zeros((ar_len,3))
    for i in range(ar_len):
        edges_ar[i,0]=int(data.pop(0))
        edges_ar[i,1]=int(data.pop(0))
        edges_ar[i,2]=int(data.pop(0))
    return edges_ar

def make_graph(file,size=1000):
    edges = read_file(file)
    im = Image.new('RGB',(size,size))
    num_nodes = int(np.max(edges[:,0]))+1
    im = make_nodes(im,num_nodes)
    im = make_edges(im,num_nodes,edges)
    im.save("out.png")

# make_graph("dataout.txt")
import sys
make_graph(sys.argv[1])