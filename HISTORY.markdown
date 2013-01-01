## [v2.0.0 (2013-01-01)](/4-20ma/I2cDiscreteIoExpander/tree/v2.0.0)
- Rename I2cDiscreteIoExpander.{cpp, h} files
- Update copyright year
- Rename class I2cDiscreteIoExpander

---
## [v1.0.1 (2012-12-31)](/4-20ma/I2cDiscreteIoExpander/tree/v1.0.1)
- Remove redundant text from README

---
## [v1.0.0 (2012-12-31)](/4-20ma/I2cDiscreteIoExpander/tree/v1.0.0)
- Add documentation
- Add blank HISTORY.markdown
- Add README.markdown
- Add SCHEMATIC depicting basic connections
- Add new examples
- Remove deprecated examples
- Rename i2c_dio_pcf8575c.* to I2cIoExpander.*
- Revise interface
- remove digitalWrite(); keep overloaded digitalWrite(uint16_t)
- rename id() to getAddress();
- add function getPorts(); remove public member data
- rename (public) member data to (private) ports_;
- rename member _u8DeviceID to address_;
- rename member _bInvert to shouldInvert_;
- rename constant _ku8BaseAddress to BASE_ADDRESS_;
- Remove deprecated begin() function
- Relocate/rename class constants
- Require Arduino 1.0 or later
- Add documentation for similar remote I/O expanders
- Rename class I2cIoExpander
- Remove .svn from .gitignore
- Fix GITHUB_REPO value
- Add TODO items to header file
- Reformat source comments (use \token v. @token)
- Reformat/relocate library description
- Add support for Arduino >= 1.0
- Replace source code dividers
- Remove unused BOUND utility macro
- Add rake tasks for preparing/releasing source
- Add VERSION file
- Initial commit
