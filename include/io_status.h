#ifndef IMAGE_TRANSFORMER_IO_STATUS_H
#define IMAGE_TRANSFORMER_IO_STATUS_H

enum request_type {
  SEPIA_TYPE = 0,
  ROTATE_TYPE
};

enum read_status {
  READ_OK = 0,
  READ_INVALID_FILENAME,
  READ_INVALID_HEADER,
  READ_INVALID_SIGNATURE,
  READ_INVALID_DATA,
  READ_UNEXPECTED_EOF,
  READ_ERROR,
  READ_CANNOT_ALLOCATE,
};

enum write_status {
  WRITE_OK = 0,
  WRITE_INVALID_FILENAME,
  WRITE_CREATE_ERROR,
  WRITE_HEADER_ERROR,
  WRITE_ERROR
};

#endif // IMAGE_TRANSFORMER_IO_STATUS_H
