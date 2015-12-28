
#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <gphoto2/gphoto2.h>

#define CAPTURE_FILE "0000.jpg"

static void ctx_error_func(GPContext *ctx, const char *str, void *data);
static void ctx_status_func(GPContext *ctx, const char *str, void *data);

static void error_dump(GPLogLevel level, const char *domain, const char *str, void *data);

int main(int argc, char *argv[])
{
	GPContext *ctx = gp_context_new();
	gp_context_set_error_func(ctx, ctx_error_func, 0);
	gp_context_set_status_func(ctx, ctx_status_func, 0);

	//gp_log_add_func(GP_LOG_ERROR, error_dump, 0);

	Camera *cam;
	gp_camera_new(&cam);

	int rv = gp_camera_init(cam, ctx);
	assert(rv == GP_OK);

	CameraFilePath path;
	strcpy(path.folder, "/");
	strcpy(path.name, "foo.jpg");

	rv = gp_camera_capture(cam, GP_CAPTURE_IMAGE, &path, ctx);
	assert(rv == GP_OK);

	CameraFile *file;
	int fd = open(CAPTURE_FILE, O_CREAT | O_WRONLY, 0644);
	rv = gp_file_new_from_fd(&file, fd);
	assert(rv == GP_OK);
	gp_camera_file_get(cam, path.folder, path.name, GP_FILE_TYPE_NORMAL, file, ctx);
	assert(rv == GP_OK);
	gp_camera_file_delete(cam, path.folder, path.name, ctx);
	assert(rv == GP_OK);
	gp_file_free(file);

	printf("%s written\n", CAPTURE_FILE);
}

static void ctx_error_func(GPContext *ctx, const char *str, void *data)
{
	fprintf(stderr, "%s\n", str);
}

static void ctx_status_func(GPContext *ctx, const char *str, void *data)
{
	fprintf(stderr, "%s\n", str);
}

static void error_dump(GPLogLevel level, const char *domain, const char *str, void *data)
{
	printf("%s\n", str);
}
