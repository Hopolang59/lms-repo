-- Moderated LMS database schema (design document, section 4.4)
-- Create with: sqlite3 lms.db < db/schema.sql

PRAGMA foreign_keys = ON;

CREATE TABLE department (
  department_id INTEGER PRIMARY KEY AUTOINCREMENT,
  name TEXT NOT NULL UNIQUE
);

CREATE TABLE users (
  user_id INTEGER PRIMARY KEY AUTOINCREMENT,
  username TEXT NOT NULL UNIQUE,
  password_hash TEXT NOT NULL,
  salt TEXT NOT NULL,
  role TEXT NOT NULL CHECK (role IN ('ADMIN','LECTURER','HOD','STUDENT')),
  is_active INTEGER NOT NULL DEFAULT 1 CHECK (is_active IN (0,1)),
  department_id INTEGER REFERENCES department(department_id),
  CHECK (role = 'ADMIN' OR department_id IS NOT NULL)
);
CREATE UNIQUE INDEX one_hod_per_department
  ON users(department_id) WHERE role = 'HOD';

CREATE TABLE course (
  course_id INTEGER PRIMARY KEY AUTOINCREMENT,
  code TEXT NOT NULL UNIQUE,
  title TEXT NOT NULL,
  department_id INTEGER NOT NULL REFERENCES department(department_id)
);

CREATE TABLE enrolment (
  course_id INTEGER NOT NULL REFERENCES course(course_id),
  student_id INTEGER NOT NULL REFERENCES users(user_id),
  enrolled_on TEXT NOT NULL,
  unenrolled_on TEXT,
  PRIMARY KEY (course_id, student_id)
);

CREATE TABLE course_lecturer (
  course_id INTEGER NOT NULL REFERENCES course(course_id),
  lecturer_id INTEGER NOT NULL REFERENCES users(user_id),
  PRIMARY KEY (course_id, lecturer_id)
);

CREATE TABLE assignment (
  assignment_id INTEGER PRIMARY KEY AUTOINCREMENT,
  course_id INTEGER NOT NULL REFERENCES course(course_id),
  title TEXT NOT NULL,
  description TEXT,
  deadline TEXT NOT NULL,
  max_mark REAL NOT NULL CHECK (max_mark > 0),
  created_by INTEGER NOT NULL REFERENCES users(user_id),
  created_at TEXT NOT NULL
);

CREATE TABLE extension (
  extension_id INTEGER PRIMARY KEY AUTOINCREMENT,
  assignment_id INTEGER NOT NULL REFERENCES assignment(assignment_id),
  student_id INTEGER NOT NULL REFERENCES users(user_id),
  new_deadline TEXT NOT NULL,
  reason TEXT NOT NULL,
  granted_by INTEGER NOT NULL REFERENCES users(user_id),
  granted_at TEXT NOT NULL
);

CREATE TABLE submission (
  submission_id INTEGER PRIMARY KEY AUTOINCREMENT,
  assignment_id INTEGER NOT NULL REFERENCES assignment(assignment_id),
  student_id INTEGER NOT NULL REFERENCES users(user_id),
  file_path TEXT NOT NULL,
  submitted_at TEXT NOT NULL,
  resubmissions INTEGER NOT NULL DEFAULT 0,
  status TEXT NOT NULL CHECK (status IN
    ('SUBMITTED','LATE','MARKED','MODERATED','RELEASED')),
  days_late INTEGER NOT NULL DEFAULT 0 CHECK (days_late >= 0),
  awarded_mark REAL CHECK (awarded_mark >= 0),
  feedback TEXT,
  marked_by INTEGER REFERENCES users(user_id),
  marked_at TEXT,
  moderated_by INTEGER REFERENCES users(user_id),
  moderated_at TEXT,
  released_at TEXT,
  UNIQUE (assignment_id, student_id)
);

CREATE TABLE audit_log (
  log_id INTEGER PRIMARY KEY AUTOINCREMENT,
  submission_id INTEGER NOT NULL REFERENCES submission(submission_id),
  changed_by INTEGER NOT NULL REFERENCES users(user_id),
  changed_at TEXT NOT NULL,
  old_value REAL,
  new_value REAL NOT NULL,
  reason TEXT NOT NULL
);
CREATE TRIGGER audit_no_update BEFORE UPDATE ON audit_log
BEGIN SELECT RAISE(ABORT, 'audit log is read-only'); END;
CREATE TRIGGER audit_no_delete BEFORE DELETE ON audit_log
BEGIN SELECT RAISE(ABORT, 'audit log is read-only'); END;

CREATE INDEX idx_enrolment_student ON enrolment(student_id);
CREATE INDEX idx_submission_student ON submission(student_id);
CREATE INDEX idx_assignment_course ON assignment(course_id);
