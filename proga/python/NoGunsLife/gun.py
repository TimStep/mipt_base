import math
from random import randint as rnd
from random import choice

import pygame
import pygame.freetype
pygame.init()

FPS = 30

RED = 0xFF0000
BLUE = 0x0000FF
YELLOW = 0xFFC91F
GREEN = 0x00FF00
MAGENTA = 0xFF03B8
CYAN = 0x00FFCC
BLACK = (0, 0, 0)
WHITE = 0xFFFFFF
GREY = 0x7D7D7D
GAME_COLORS = [RED, BLUE, YELLOW, GREEN, MAGENTA, CYAN]

WIDTH = 800
HEIGHT = 600
GAME_FONT = pygame.freetype.SysFont('Comic Sans MS', 16)

class Ball:
    def __init__(self, screen: pygame.Surface, x=40, y=450):
        """ Конструктор класса ball

        Args:
        x - начальное положение мяча по горизонтали
        y - начальное положение мяча по вертикали
        """
        self.screen = screen
        self.x = x
        self.y = y
        self.r = 10
        self.vx = 0
        self.vy = 0
        self.color = choice(GAME_COLORS)
        self.live = 30

    def move(self):
        """Переместить мяч по прошествии единицы времени.

        Метод описывает перемещение мяча за один кадр перерисовки. То есть, обновляет значения
        self.x и self.y с учетом скоростей self.vx и self.vy, силы гравитации, действующей на мяч,
        и стен по краям окна (размер окна 800х600).
        """
        # FIXME - gravity and bouncing off edges DONE
        global WIDTH
        if self.x + self.r >= WIDTH: self.vx *= -1
        if self.y - self.r <= 0: self.vy *= -1
        self.x += self.vx
        self.vy -= 0.4 #0.4 gravity coefficient
        self.y -= self.vy

    def draw(self):
        pygame.draw.circle(
            self.screen,
            self.color,
            (self.x, self.y),
            self.r
        )

    def hittest(self, obj):
        """Функция проверяет сталкивалкивается ли данный обьект с целью, описываемой в обьекте obj.

        Args:
            obj: Обьект, с которым проверяется столкновение.
        Returns:
            Возвращает True в случае столкновения мяча и цели. В противном случае возвращает False.
        """
        # FIXME - collision check DONE
        if (self.x - obj.x)**2 + (self.y - obj.y)**2 < (self.r + obj.r)**2:
        	return True
        else:
        	return False


class Gun:
    def __init__(self, screen):
        self.screen = screen
        self.f2_power = 10
        self.f2_on = 0
        self.an = 1
        self.color = GREY
        self.x = 20
        self.y = 450
        self.l = 20
        self.w = 10
        #self.pos = pygame.Rect(20, 450, 20, 10)

    def fire2_start(self, event):
        self.f2_on = 1

    def fire2_end(self, event):
        """Выстрел мячом.

        Происходит при отпускании кнопки мыши.
        Начальные значения компонент скорости мяча vx и vy зависят от положения мыши.
        """
        global balls, bullet
        bullet += 1
        new_ball = Ball(self.screen)
        new_ball.r += 5
        self.an = math.atan2((event.pos[1]-new_ball.y), (event.pos[0]-new_ball.x))
        new_ball.vx = self.f2_power * math.cos(self.an)
        new_ball.vy = - self.f2_power * math.sin(self.an)
        balls.append(new_ball)
        self.f2_on = 0
        self.f2_power = 10

    def targetting(self, event):
        """Прицеливание. Зависит от положения мыши."""
        if event:
            try:
                self.an = math.atan((event.pos[1]-self.y) / (event.pos[0]-self.x))
            except:
                pass
        if self.f2_on:
            self.color = RED
            #self.l = 40
        else:
            self.color = GREY
            #self.l = 20

    def draw(self):
    	
        # FIXIT draw and rotate - DONE
        #TODO: rotate over left side, not center
        
        #pygame.draw.rect(self.screen, self.color, self.pos)
        
        '''
        rot_center = (self.x - self.l/2, self.y)
        radius1 = self.w/2
        radius2 = math.sqrt(self.l**2 + (self.w/2)**2)
        '''
        points = []
        radius = math.sqrt((self.w/2)**2 + (self.l/2)**2)
        angle = math.atan2(self.w, self.l)
        angles = [angle, -1*angle + math.pi, angle + math.pi, -1*angle]
        
        for angle in angles:
        	y_offset = 1*radius*math.sin(angle+self.an)
        	x_offset = radius*math.cos(angle+self.an)
        	points.append((self.x + x_offset, self.y + y_offset))
        
        '''
        x_offset1 = radius1*math.cos(self.an)
        y_offset1 = radius1*math.sin(self.an)
        x_offset2 = radius2*math.cos(self.an)
        y_offset2 = radius2*math.sin(self.an)
        
        points = [(self.x + self.l/2 - x_offset2, self.y + self.w/2 + y_offset2), (self.x - self.l/2 - x_offset2, self.y + self.w/2 - y_offset2), (self.x - self.l/2 + x_offset2, self.y - self.w/2 - y_offset2), (self.x + self.l/2 + x_offset2, self.y - self.w/2 + y_offset2)]
        '''
        pygame.draw.polygon(self.screen, self.color, points)

    def power_up(self):
        if self.f2_on:
            if self.f2_power < 100:
                self.f2_power += 1
            self.color = RED
            if self.l <= 60: self.l+=1
        else:
            self.color = GREY
            self.l = 20


class Target:
    # self.points = 0
    # self.live = 1
    # FIXME: don't work!!! How to call this functions when object is created? - divide and rewrite init and new_target functions (clumsy solution => TODO) - DONE
    # self.new_target()
    
    def __init__(self, screen):
    	self.points = 0
    	self.live = 1
    	self.screen = screen
    	self.color = RED
    	self.x = rnd(600, 780)
    	self.y = rnd(300, 550)
    	self.r = rnd(5, 30)
    	self.vx = rnd(1, 10)
    	self.vy = rnd(1, 10)
    	
    def new_target(self):
        """ Инициализация новой цели. """
        self.live = 1
        self.x = rnd(600, 780)
        self.y = rnd(300, 550)
        self.r = rnd(5, 30)
        self.color = RED

    def hit(self, points=1):
        """Попадание шарика в цель."""
        self.points += points

    def draw(self):
        pygame.draw.circle(
            self.screen,
            self.color,
            (self.x, self.y),
            self.r
        )

    def move(self):
    	global WIDTH, HEIGHT
    	if self.x - self.r <= 0 or self.x + self.r >= WIDTH: self.vx *= -1
    	if self.y - self.r <= 0 or self.y + self.r >= HEIGHT: self.vy *= -1
    	self.x += self.vx
    	self.y -= self.vy


pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
bullet = 0
balls = []

clock = pygame.time.Clock()
gun = Gun(screen)
target1 = Target(screen)
target2 = Target(screen)
targets = [target1, target2]
finished = False

while not finished:
    screen.fill(WHITE)
    gun.draw()
    target1.draw()
    target2.draw()
    for b in balls:
        b.draw()
    GAME_FONT.render_to(screen, (10, 10), str(target1.points + target2.points), (0, 0, 0))
    pygame.display.update()
    
    clock.tick(FPS)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            finished = True
        elif event.type == pygame.MOUSEBUTTONDOWN:
            gun.fire2_start(event)
        elif event.type == pygame.MOUSEBUTTONUP:
            gun.fire2_end(event)
        elif event.type == pygame.MOUSEMOTION:
            gun.targetting(event)

    for target in targets:
        target.move()
        for b in balls:
            b.move()
            if b.hittest(target) and target.live:
                target.live = 0
                target.hit()
                target.new_target()
            #print(target.points)
    gun.power_up()

pygame.quit()
