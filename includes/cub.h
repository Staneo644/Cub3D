/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:13:10 by tlafay            #+#    #+#             */
/*   Updated: 2022/05/10 14:29:47 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>

# include "get_next_line.h"
# include "mlx.h"

//touches du clavier

# define UP 13
# define LEFT 0
# define RIGHT 2
# define DOWN 1

//taille de l'écran

# define SIZE_SCREEN_HEIGHT 1080
# define SIZE_SCREEN_WIDTH 1920
# define INV_SIZE_SCREEN_HEIGHT 0.000926
# define INV_SIZE_SCREEN_WIDTH 0.00052084
# define SIZE_SCREEN_HEIGHT2 540
# define SIZE_SCREEN_WIDTH2 960

//rendu

# define MINIMAP_P_SIZE 5
# define MINIMAP_HEIGHT 850
# define MINIMAP_WIDTH 5
# define FOV 1.91986
# define SPEED 0.1
# define SPEED_TURN_VIEW 0.1
# define WALL_HEIGHT 700

//# define SIZE_PRECISION 1

//orientation

# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4

typedef struct s_press_key
{
	int	up_p;
	int	down_p;
	int	right_p;
	int	left_p;

}	t_press_key;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_map
{
	char	*nofd;
	char	*sofd;
	char	*wefd;
	char	*eafd;

	int		*c;
	int		*f;

	char	**map;
}	t_map;

typedef struct s_pos
{
	double	p_x;
	double	p_y;
	double	angle_of_view;
}	t_pos;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_texture
{
	t_image	img;
	int		height;
	int		width;
}	t_texture;

typedef struct s_cub
{
	void			*mlx;
	void			*win;
	t_press_key		key;
	t_image			img;
	t_image			tmp;
	t_pos			pos;
	t_map			map;
	double			old_x;
	struct timeval	last_time;
	t_texture		so_text;
	t_texture		no_text;
	t_texture		we_text;
	t_texture		ea_text;
}	t_cub;

typedef struct s_line
{
	t_cub	*game;
	t_image	img;
	int		x;
	double	distance;
}	t_line;

/********    check_map.c    ********/

int			ft_check_with_zero(char **str, int i, int j);
int			ft_for_norminette(int i, int j);
int			ft_check_map_error(char **str, int i);

/********    colors.c    ********/

int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
int			create_trgb(int t, int r, int g, int b);

/********    draw.c    ********/

int			draw_floor(t_image *img, int color, int x, double diff);
t_texture	get_texture(t_cub *game, int orientation);
t_image		draw_walls(t_line line, t_texture text, int *height, double hit);
t_image		draw_ceiling(t_image img, int height, int color, int x);

/********    file_color_parse.c    ********/

char		*ft_add_to_str(char *str, char c);
int			ft_second_file_parse(char c, int fd, char **ret_fd);
int			ft_file_parse(char err, char search, char **ret_fd, int fd);
int			ft_init_color(int **color);
int			ft_color_parse(char err, int **color, int fd);

/********    ft_itoa.c    ********/

int			digit_num(long n);
void		get_tab(int i, long s, char *ret);
char		*ft_itoa(long n);

/********    get_next_line.c    ********/

char		*get_next_line(int fd);

/********    hooks.c    ********/

int			ft_close(t_cub *game);
int			ft_key(int a, t_cub *game);
int			ft_key_release(int a, t_cub *game);
int			mouse_turn(int x, int y, t_cub *game);
int			render_next_frame(t_cub *game);

/********    init_struct.c    ********/

int			ft_init_pos(t_cub *game, char a);
int			ft_init_cub(t_cub *game, t_map *map);
void		check_xpms(t_cub *game);
void		load_xpms(t_cub *game);

/********    launch_ray.c    ********/

t_point		ray_args(t_pos pos, t_point unit_step, t_point angle, t_point *ray);
double		ray_inc(int *coord, double inc, double *ray, double unit_step);
double		orientate(double angle, int or1, int or2);
void		launch_ray(t_cub *game, t_point angle,
				double *distance, int *orientation);

/********    libft.c    ********/

int			ft_atoi(char firtst_nb, int *num, int fd, char delimited_char);
int			ft_strlen(char *str);
int			ft_free(void *str);
int			ft_error(char *str);
void		*ft_malloc(size_t x);

/********    map_parse.c    ********/

int			ft_pstrlen(char **str);
int			ft_free_pstr(char **pstr);
char		**ft_add_to_pstr(char **pstr, char *str);
int			ft_map_pars(int fd, t_map *map);

/********    minimap.c    ********/

t_image		draw_square(t_image img, int x, int y, int color);
t_image		minimap(t_image img, t_cub *game);

/********    parsing.c    ********/

char		ft_mute_char(int fd, char muted, int type);
int			ft_redirect_char(char a, int fd, t_map *map);
int			ft_main_pars(int fd, t_map *map);
int			main(int argc, char **argv);

/********    pixels.c    ********/

void		my_mlx_pixel_put(t_image *img, int x, int y, int color);
int			get_pixel(t_image *img, int x, int y);
int			better_get_pixel(t_texture text, int x, int y);
void		better_pixel_put(t_image *img, int x, int y, int color);

/********    process.c    ********/

int			ft_move(t_cub *game, t_pos *pers, int x, int y);
t_image		ft_draw_frame(t_image img, t_cub *game);
int			ft_search_p(char **argv, char a, int x);
int			ft_next_pars(t_map *map);

/********    raycast.c    ********/

t_image		vertical_line(t_line line, t_point pos, int orientation);
t_point		calculate_diff(t_cub *game, int x, double H, double unit);
t_line		init_line(t_cub *game, t_image img, int x, double distance);
t_image		raycast(t_image img, t_cub *game);

/********    t_map_func.c    ********/

int			ft_is_not_full(t_map *map);
void		ft_initialise_map(t_map *map);
int			ft_free_map(t_map *map, int fd);

/********    utils.c    ********/

long		time_diff(struct timeval start, struct timeval end);
int			invert_y(int y, int height);
void		ft_exit(char *str);
double		ft_fabs(double num);

/********    write_func.c    ********/

int			ft_write_pstr(char **pstr);
void		ft_write_map(t_map *map);
int			ft_putc(char a);
int			ft_put(char *str);
int			ft_putnb(int nb);

#endif